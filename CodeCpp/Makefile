LIBPATH=-L./chilkat/lib/libchilkat-9.5.0.so
LIBS=-lchilkat-9.5.0 -lpthread -lstdc++fs
program:   MyTime.o exec.o Unzip.o main.o config.o equalFiles.o xmlMake.o
	g++  MyTime.o exec.o Unzip.o main.o config.o equalFiles.o xmlMake.o  ${LIBPATH} ${LIBS} -o program -std=c++17
MyTime.o: MyTime.cpp
	g++ -c MyTime.cpp -std=c++17
exec.o: exec.cpp
	g++ -c exec.cpp -std=c++17
Unzip.o: Unzip.cpp
	g++ -c Unzip.cpp -std=c++17
main.o: main.cpp
	g++ -c main.cpp -std=c++17
config.o: config.cpp
	g++ -c config.cpp -std=c++17
equalFiles.o: equalFiles.cpp
	g++ -c equalFiles.cpp -std=c++17
xmlMake.o: xmlMake.cpp
	g++ -c xmlMake.cpp -std=c++17
clean:
	rm -rf *.o
