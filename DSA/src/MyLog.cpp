#include "../include/MyLog.h"
#include "../include/MyException.h"
#include "../include/FileProcess.h"
#include "../include/Resource.h"
#include "../include/MyUtility.h"
#include <ctime>
using namespace std;
SystemLog* SystemLog::s_instance=nullptr;
SystemLog::SystemLog()
{
	log.exceptions(ofstream::failbit|ofstream::badbit);
	setLogFile("/etc/onlinejudge/log.log");
}
SystemLog* SystemLog::instance()
{
	
	static SystemLog s_instance;
	return &s_instance;
}
void SystemLog::setLogFile(const string& fileLog,bool append)
{
	if(append)
		log.open(fileLog,ios::out|ios::app);
	else log.open(fileLog,ios::out);
}
void SystemLog::WriteToConsole(const string& str)
{
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
	cout << string(buf) << " " << str << endl;
}
void SystemLog::WriteToFile(const string& str,bool Debug)
{
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
	log << string(buf) << " " << str << endl;
	if(Debug) cout<<string(buf)<<" "<<str<<endl;
}
SystemLog::~SystemLog()
{
	log.close();
}

StudentLog::StudentLog(const FileInfo& fileInfo)
{
	//format @sourcePath: ../ass1/1611695/1
	//format: ass1.1611695.1
	fs::path p(fileInfo.path);
	string id=p.filename().string();
	string idStudent=p.parent_path().filename().string();
	string assname=p.parent_path().parent_path().filename().string();
	filename=assname+"."+idStudent+"."+id;
	log.open(Resource::lock_path()+"/"+filename,ios::out|ios::app);
	if(!log.is_open())
	{
		throw MyException("Can't open "+filename+" to write!");
	}
}
void StudentLog::WriteToConsole(const string& str)
{
	cout<<str<<endl;
}
void StudentLog::WriteToFile(const string& str)
{
	log<<str<<endl;
}
string StudentLog::getFilePath()
{
	return Resource::lock_path()+"/"+filename;
}
StudentLog::~StudentLog()
{
	string des=filename;
	for(int i=0;i<filename.size();++i) if(des[i]=='.') des[i]='/';
		File(Resource::lock_path()+"/"+filename).moveTo(Resource::source_path()+"/"+des+"/log.txt");
}
