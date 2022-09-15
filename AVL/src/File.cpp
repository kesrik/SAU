#include "File.hpp"

File::File()
{
}

AVL *avl = new AVL();

string File::ltrim(const string &s) const
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == string::npos) ? "" : s.substr(start);
}

string File::rtrim(const string &s) const
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == string::npos) ? "" : s.substr(0, end + 1);
}

string File::trim(const string &s) const
{
    return rtrim(ltrim(s));
}

int File::sumOfArray(int *array, int arrayLength) const
{
    int sum = 0;
    for (int i = 0; i < arrayLength; i++)
    {
        sum += array[i];
    }
    return sum;
}

void File::read(string &filePath) const
{
    ifstream file(filePath);
    string row;

    system("cls");

    while (getline(file, row))
    {
        int spaceCount = 0;

        row = trim(row);

        if (row == "")
            continue;

        for (int i = 0; i < row.length(); i++)
        {
            if (row[i] == ' ')
            {
                spaceCount++;
            }
        }
        int numbersSize = spaceCount;

        int *numbers = new int[numbersSize + 1];

        int j = 0;

        for (int i = 0; i < row.length(); i++)
        {
            if (row[i] == ' ') // since this if statement only occurs when there is a space at i index of the string, we can't update the last numbers here
            {
                numbers[j] = stoi(row.substr(0, i));
                row = row.substr(i + 1);
                j++;
                i = 0;
            }
        }

        numbers[j] = stoi(row); // update the last numbers here
        avl->ArrAdd(sumOfArray(numbers, j + 1), numbers, j + 1);
    }
    avl->preorder();
    delete avl;
}

File::~File()
{
}