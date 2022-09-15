// Blynk credentials
#define BLYNK_TEMPLATE_ID ""
#define BLYNK_DEVICE_NAME ""
#define BLYNK_AUTH_TOKEN ""

#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <BlynkSimpleEsp8266.h>

// Firebase credentials
#define FIREBASE_HOST "" 
#define FIREBASE_AUTH ""

// Blynk variables
bool isOn;
int maxTemp, minTemp, gauge;
int user;
char auth[] = BLYNK_AUTH_TOKEN;
String terminalLine;

// Firebase variables
FirebaseData myDatabase;
int fireMinTemp, fireMaxTemp;
int fireUser;

// WiFi credentials
char ssid[] = "";
char pass[] = "";

BlynkTimer timer;

// update isOn when the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  if (param.asInt() == 1) isOn = true;
  else isOn = false;
}

// update maxTemp when the Virtual Pin 1 state changes
BLYNK_WRITE(V1)
{
  maxTemp = param.asInt();
  if (user == 1)
    Firebase.setString(myDatabase, F("/u1MaxTemp"), maxTemp);
  else if (user == 2)
    Firebase.setString(myDatabase, F("/u2MaxTemp"), maxTemp);
}

//  update minTemp when the Virtual Pin 2 state changes
BLYNK_WRITE(V2)
{
  minTemp = param.asInt();
  if (user == 1)
    Firebase.setString(myDatabase, F("/u1MinTemp"), minTemp);
  else if (user == 2)
    Firebase.setString(myDatabase, F("/u2MinTemp"), minTemp);
}

// update user when the Virtual Pin 5 state changes
BLYNK_WRITE(V5)
{
  if (user == 0 || user == 1 || user == 2)
    user = param.asInt();
  Serial.print("user changed to ");
  Serial.println(user);

  Firebase.setString(myDatabase, F("/user"),  String(user));
  Blynk.virtualWrite(V5, "user updated to: " + String(user) + "\n");
}

// This function sends Arduino's uptime every second to Virtual Pin 4.
void myTimerEvent()
{
  Blynk.virtualWrite(V4, millis() / 1000);
}

int sensor = A0;
float tempValue;   //analog value converted into temperature in celsius 
float measuredValue;   //measured analog value
int islem = 1; //idling


void setup() {
  Serial.begin(9600);  // Serial port baud rate 

  pinMode(A0,INPUT);

  //Firebase connect
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
  Blynk.begin(auth, ssid, pass);
  
  Blynk.virtualWrite(V0, 0);  //update isOn as 0 at setup
  Blynk.virtualWrite(V5, "user updated to: " + String(0) + "\n");
   
  Firebase.setString(myDatabase, F("/user"), user); //update user as 0 at setup 

  //Firebase reconnect if there's an interruption in the connection
  Firebase.reconnectWiFi(true);

  timer.setInterval(1000L, myTimerEvent);
}

void loop() {
  // LM35 
  measuredValue = analogRead(sensor); 
  measuredValue = (measuredValue/1024)*3300;
  tempValue = measuredValue /10;
  
  if (isOn)
  {
    Serial.print("Measured Temp: "); 
    Serial.print(tempValue);
    Serial.println(" C");
    Blynk.virtualWrite(V3, tempValue);

    if (fireUser == 0)
    {
      Serial.println("user undefined");
    }
    else if (fireUser == 1)
    {
      Serial.println("user 1 min temp updated");
      if (Firebase.getString(myDatabase, "/u1MinTemp"))
      {
         fireMinTemp = myDatabase.stringData().toInt();
         Blynk.virtualWrite(V2,fireMinTemp);
      }
      Serial.println("user 1 max temp updated");
      if (Firebase.getString(myDatabase, "/u1MaxTemp"))
      {
         fireMaxTemp = myDatabase.stringData().toInt();
         Blynk.virtualWrite(V1,fireMaxTemp);
      }
    }
    else if (fireUser == 2)
    {
      Serial.println("user 2 min temp updated");
      if (Firebase.getString(myDatabase, "/u2MinTemp"))
      {
         fireMinTemp = myDatabase.stringData().toInt();
         Blynk.virtualWrite(V2, fireMinTemp);
      }
      Serial.println("user 2 max temp updated");
      if (Firebase.getString(myDatabase, "/u2MaxTemp"))
      {
         fireMaxTemp = myDatabase.stringData().toInt();
         Blynk.virtualWrite(V1, fireMaxTemp);
      }
    }

    
    
    if (Firebase.getString(myDatabase, "/user"))
    {
      fireUser = myDatabase.stringData().toInt();
      if (fireUser != user)
      {
        user = fireUser;
        Blynk.virtualWrite(V5, "user updated to: " + String(user) + "\n");
        if (myDatabase.stringData()=="0")
        {
            Serial.println("fireUser undefined");
        }  
        else if (myDatabase.stringData()=="1")
        {
            Serial.println("user 1");
        }
        else if (myDatabase.stringData()=="2")
        {
            Serial.println("user 2");
        }  
        else 
        {
            Serial.println("Error");
        }  
      }
    }
    
    if (user != 0 && tempValue > maxTemp)
    {
      Serial.println("lowering temperature");
      if (islem != 2)
      {
        Serial.println("process defined as cooling");
        islem = 2; //cooling
      }
    }
    
    if (user != 0 && tempValue < minTemp) 
    {
      Serial.println("increasing temperature");
      if (islem != 1)
      {
        Serial.println("process defined as heating");
        islem = 1; //heating
      }
    }
    
    if (user != 0 && tempValue < maxTemp - 1 && tempValue > minTemp + 1) 
    {
      Serial.println("idling");
      if (islem != 0)
      {
        Serial.println("process defined as idling");
        islem = 0; //idling
      }
    }
  }
  
  
  Blynk.run();
  timer.run();
  
  delay (1000);
}
