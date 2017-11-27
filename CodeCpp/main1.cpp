#include "File.h"
#include "exec.h"
#include "Unzip.h"
#include "MyTime.h"
#include <exception>
#include <thread>
#include <iostream>
#include <cstdlib>
#include <queue>
#include <fstream>
#include <unistd.h>
#include <regex>
#include "chilkat/include/CkZip.h"


string uploadPath="/home/tuankiet/Project/Upload";
string lockPath="/home/tuankiet/Project/lock";
string sourcePath="/home/tuankiet/Project/Source";
int delay=1000;//ms
struct FileInfo
{
	string path;
	long timeStamp;
};
bool operator<(const FileInfo& op1, const FileInfo& op2)
{
	return op1.timeStamp>op2.timeStamp;
}
string getLogFile(const string& dir)
{
	return lockPath+"/"+File(Directory(dir).getParentDirectory()).getFilenameOnly()+"."+File(dir).getFilename()+".log";
}
priority_queue<FileInfo> fileList;   


class MyException:public exception
{
    private:
    string text;
    public:
    MyException(const string& str)
    {
        text=str;
    }
    char const* what() const throw()
    {
        return text.c_str();
    }
};

string getFolder(const string path)
{
    try
    {
	regex r("([0-9]*)_([0-9]*)");
	smatch m;
	string name;
	string filename=File(path).getFilenameOnly();
	if(regex_match(filename,m,r))
	{
		name=m[1];
	}
	else
	{
		throw MyException("invalid format file name");
	}
	string parent=Directory(path).getParentDirectory();
	int index=Directory(sourcePath+"/"+name).dirsCount()+1;
	return name+"/"+to_string(index);
    }
    catch(exception& e)
    {
        throw;
    }
}

void addFileList()
{

    try
    {
	Directory dir(uploadPath);
	vector<string> lst=dir.getListFile();
		if(lst.size()==0) return;
	for(auto& i : lst)
	{	
		
		string dirPath=sourcePath+"/"+getFolder(i);
		if(!Directory::create(dirPath))
		{
			throw MyException("Can't create directory "+dirPath);
		}

		if(!Unzip(i,dirPath))
		{
			throw MyException("Unzip error filename: "+dirPath);
		}
		else
		{
			fstream f(getLogFile(dirPath),ios::out|ios::app);
			f.close();
		}
		fileList.emplace(FileInfo{dirPath,getTimeStamp(i)});
		File(i).deleteFile();
	}
		
    }
    catch(exception& e)
    {
        throw;
    }
}
void compile(const string& dir, const string& logfile)
{
    try
    {
	string cmd2="cd "+dir+";g++ -o program *.cpp";
    bool succ;
	string str=Run(cmd2,succ,logfile);
	if(!succ)
	{
		throw MyException(str);
	}
    }
    catch(exception& e)
    {
	    throw;
    }
}
void Excute(const string& dir)
{
	try
	{
		string logfile=getLogFile(dir);
		fstream f(logfile,ios::out|ios::app);
		f.close();
		compile(dir,logfile);
		//RunProgram(dir);
		//CheckPoint(dir);
		if(File(logfile).isFileEmpty()) File(logfile).deleteFile();
	}
	catch(exception& e)
	{
		string filename=getLogFile(dir);
       	fstream f(filename,ios::out|ios::app);
	    f<<e.what();
	    f.close();
	    File(filename).moveTo(dir+"/log.txt");
	}
}
void Recover()
{
	vector<string> lst=Directory(lockPath).getListFile();
	if(lst.size()>0)
	{
		cout<<"Found lock file in lock directory\n";
		cout<<"Do you want to recover last sesion(Y/N): ";
		string str;
		getline(cin,str);
		cout<<str<<endl;
		while(str!="Y"&&str!="N"&&str!="y"&&str!="n")
		{
			cout<<"Input error, try again!\n";
			getline(cin,str);
		}
		if(str=="n"||str=="N")
		{
			cout<<"Don't recover last sesion, removing the lock files.....\n";
			for(auto& p:lst) File(p).deleteFile();
		}
		else
		{
			cout<<"Recovering the last sesion.....\n";
			for(auto& p:lst)
			{
				string filename=File(p).getFilenameOnly();
				for(int i=0;i<filename.size();++i) if(filename[i]=='.') filename[i]='/';
				fileList.emplace(FileInfo{sourcePath+"/"+filename,0});
			}
		}
	}
}
int main()
{
	Recover();
	while(true)
	{
	try
	{
		addFileList();
		vector<thread> arrThread;
		while(!fileList.empty())
		{
			FileInfo fileInfo=fileList.top();
			fileList.pop();
			arrThread.push_back(thread(Excute,fileInfo.path));

		}
		for(int i=0;i<arrThread.size();++i) arrThread[i].join();
		usleep(delay*1000);
	}
	catch(exception& e)
	{
		cout<<e.what();
	}
	catch(...)
	{
		cout<<"Unexpected error occurs...";
	}
	}
}
