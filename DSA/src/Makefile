LIBS= -lboost_system -lboost_filesystem -lboost_regex
CC=g++
CFLAGS=-w -fpermissive
CPPFLAGS=-DUSE_BOOST -std=c++11
program: ExcuteCmd.o FormatOutput.o SourcePrepare.o FileCompare.o CRM.o FileProcess.o main.o MyLog.o MyUtility.o pugixml.o Resource.o xmlProcess.o
	$(CC) ExcuteCmd.o FormatOutput.o SourcePrepare.o FileCompare.o CRM.o FileProcess.o main.o MyLog.o MyUtility.o pugixml.o Resource.o xmlProcess.o  -L"../lib/" $(LIBS) -lpthread -lZipper-static -lz  -o program
main.o:	main.cpp
	$(CC) -c $(CPPFLAGS) main.cpp
SourcePrepare.o: SourcePrepare.cpp
	$(CC) -c $(CPPFLAGS) $(CFLAGS) SourcePrepare.cpp
ExcuteCmd.o: ExcuteCmd.cpp
	$(CC) -c $(CPPFLAGS) ExcuteCmd.cpp
FileProcess.o: FileProcess.cpp
	$(CC) -c $(CPPFLAGS) FileProcess.cpp
FileCompare.o: FileCompare.cpp
	$(CC) -c $(CPPFLAGS) FileCompare.cpp
FormatOutput.o: FormatOutput.cpp
	$(CC) -c $(CPPFLAGS) FormatOutput.cpp
MyUtility.o: MyUtility.cpp
	$(CC) -c $(CPPFLAGS) MyUtility.cpp
pugixml.o: pugixml.cpp
	$(CC) -c $(CPPFLAGS) pugixml.cpp
Resource.o: Resource.cpp
	$(CC) -c $(CPPFLAGS) $(CFLAGS)  Resource.cpp
xmlProcess.o: xmlProcess.cpp
	$(CC) -c $(CPPFLAGS) $(CFLAGS) xmlProcess.cpp
CRM.o: CRM.cpp
	$(CC) -c $(CPPFLAGS) $(CFLAGS)  CRM.cpp
MyLog.o: MyLog.cpp
	$(CC) -c $(CPPFLAGS) $(CFLAGS) MyLog.cpp
clean:
	rm -rf *.o
	rm program
