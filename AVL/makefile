all: compile run

compile:
	g++ -I ./include -o ./lib/QueueNode.o -c ./src/QueueNode.cpp
	g++ -I ./include -o ./lib/Queue.o -c ./src/Queue.cpp
	g++ -I ./include -o ./lib/Radix.o -c ./src/Radix.cpp
	g++ -I ././include -o ./lib/Node.o -c ./src/Node.cpp
	g++ -I ././include -o ./lib/AVL.o -c ./src/AVL.cpp
	g++ -I ././include -o ./lib/File.o -c ./src/File.cpp
	g++ -I ./include/ -o ./bin/FileTest ./lib/QueueNode.o ./lib/Queue.o ./lib/Radix.o ./lib/Node.o ./lib/AVL.o ./lib/File.o ./src/FileTest.cpp
	
run:
	./bin/FileTest