program:   main.o exec.o
	g++  exec.o main.o -L/home/tuankiet/Project/ -lchilkat-9.5.0 -lpthread -lstdc++fs -o program
exec.o: exec.cpp
	g++ -c exec.cpp
main.o: main.cpp
	g++ -c main.cpp
