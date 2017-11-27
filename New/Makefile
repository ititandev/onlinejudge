program:   main.o exec.o Unzip.o MyTime.o
	g++  exec.o main.o Unzip.o MyTime.o -L/home/tuankiet/Project/ -lchilkat-9.5.0 -lpthread -lstdc++fs -o program
MyTime.o: MyTime.cpp
	g++ -c MyTime.cpp
exec.o: exec.cpp
	g++ -c exec.cpp
Unzip.o: Unzip.cpp
	g++ -c Unzip.cpp
main.o: main.cpp
	g++ -c main.cpp
