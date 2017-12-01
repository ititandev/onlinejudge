program:    MyTime.o exec.o Unzip.o main.o config.o equalFiles.o xmlMake.o
	g++  MyTime.o exec.o Unzip.o main.o config.o equalFiles.o xmlMake.o -lboost_regex  -lZipper-static -lz -lpthread -lboost_system -lboost_filesystem -o program
MyTime.o: MyTime.cpp 
	g++ -c MyTime.cpp -std=c++11
exec.o: exec.cpp
	g++ -c exec.cpp -std=c++11
Unzip.o: Unzip.cpp
	g++ -c Unzip.cpp -std=c++11
main.o: main.cpp
	g++ -c main.cpp -std=c++11
config.o: config.cpp
	g++ -c config.cpp -std=c++11
equalFiles.o: equalFiles.cpp
	g++ -c equalFiles.cpp -std=c++11
xmlMake.o: xmlMake.cpp
	g++ -c xmlMake.cpp -std=c++11
export: export.o 
	g++ -o export export.o -lstdc++fs -std=c++11
export.o: export.cpp
	g++ -c export.cpp -fpermissive -std=c++11
clean:
	rm -rf *.o
