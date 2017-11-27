program:   main.o exec.o
	g++  exec.o main.o -L/mnt/d/Github/DSA/ -lchilkat-9.5.0 -lpthread -lstdc++fs -o program -std=c++14
exec.o: exec.cpp
	g++ -c exec.cpp -std=c++14
main.o: main.cpp
	g++ -c main.cpp -std=c++14
