LIBPATH=-L./chilkat/lib/libchilkat-9.5.0.so
LIBS=-lchilkat-9.5.0 -lpthread -lstdc++fs
program:   MyTime.o exec.o Unzip.o main.o config.o equalFiles.o xmlMake.o
	g++  MyTime.o exec.o Unzip.o main.o config.o equalFiles.o xmlMake.o  ${LIBPATH} ${LIBS} -o program
MyTime.o: MyTime.cpp
	g++ -c MyTime.cpp
exec.o: exec.cpp
	g++ -c exec.cpp
Unzip.o: Unzip.cpp
	g++ -c Unzip.cpp
main.o: main.cpp
	g++ -c main.cpp
config.o: config.cpp
	g++ -c config.cpp
equalFiles.o: equalFiles.cpp
	g++ -c equalFiles.cpp
xmlMake.o: xmlMake.cpp
	g++ -c xmlMake.cpp
clean:
	rm -rf *.o
