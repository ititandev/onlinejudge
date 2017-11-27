#include "File.h"
#include "exec.h"
#include "Unzip.h"
#include "MyTime.h"
#include "xmlMake.h"
#include "equalFiles.h"
#include "config.h"
#include <exception>
#include <thread>
#include <iostream>
#include <cstdlib>
#include <queue>
#include <fstream>
#include <unistd.h>
#include <regex>
#include "chilkat/include/CkZip.h"

int frame, max_upload;
string timeout;
string testcase_path;
int testcase_num;
int *testcase_weight;
string log_path;
string lock_path;
string source_path;
string upload_path;

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
	return lock_path+"/"+File(Directory(dir).getParentDirectory()).getFilenameOnly()+"."+File(dir).getFilename()+".log";
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
	MyException()
	{
		text="";
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
	int index=Directory(source_path+"/"+name).dirsCount()+1;
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
	Directory dir(upload_path);
	vector<string> lst=dir.getListFile();
		if(lst.size()==0) return;
	for(auto& i : lst)
	{	
		
		string dirPath=source_path+"/"+getFolder(i);
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
	createMakefile(dir);
	string cmd2="cd "+dir+"; make";
    bool succ;
	Run(cmd2,succ,logfile);
	if(!succ)
	{
		throw MyException();
	}
    }
    catch(exception& e)
    {
	    throw;
    }
}
void Run(const string& pathToSubmit)
{
	try
	{
		string remove = "rm -f " + pathToSubmit + "/*.out";
		system(remove.c_str());
		for (size_t i = 0; i < testcase_num; i++)
		{
			string command = "timeout " + timeout +" ."+ pathToSubmit + "/program ";
			string param = testcase_path + "/" + to_string(i) + ".in " + pathToSubmit + "/" + to_string(i) + ".out";

			system((command + param +" ; if [ $? -eq 124 ]; then echo \"Timeout error\";fi"+ " &>> " + getLogFile(pathToSubmit)).c_str());                                                                                                                                                                                                                                 


			//Ghi vo log chinh va xoa log tam.... ben toi File.h bi loi
		}
	}
	catch(exception& e)
	{
		throw;
	}

}

//Tinh diem luu vo score.log
void Mark(const string& pathToSubmit)
{
	try
	{
		string remove = "rm -f " + pathToSubmit + "/score.log";
		system(remove.c_str());
		fstream file(pathToSubmit + "/score.log", ios::out);
		double score = 0;
		string ss;
		for (size_t i = 0; i < testcase_num; i++)
		{
			ss += "Testcase " + to_string(i + 1);
			ifstream origin(testcase_path + "/" + to_string(i) + ".out");
			ifstream compare(pathToSubmit + "/" + to_string(i) + ".out");
			if (equalFiles(origin, compare))
			{
				ss += ": Pass\t";
				ss += to_string(testcase_weight[i]/10) + '\n';
				score += testcase_weight[i];
			}
			else
			ss += ": Fail\t0\n";
		}
		score /= 10;
		file << "Score: \t\t\t" << score << endl;
		file << ss;
		file.close();
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
		fstream score(dir+"/"+"score.log",ios::out);
		score<<"Score:\t\t\t0\n";
		score.close();
		string logfile=getLogFile(dir);
		compile(dir,logfile);
		Run(dir);
		Mark(dir);
		File(logfile).moveTo(dir+"/log.txt");
		
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
	vector<string> lst=Directory(lock_path).getListFile();
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
			cout<<"Don't recover last session, removing the lock files.....\n";
			for(auto& p:lst) File(p).deleteFile();
		}
		else
		{
			cout<<"Recovering the last session.....\n";
			for(auto& p:lst)
			{
				string filename=File(p).getFilenameOnly();
				for(int i=0;i<filename.size();++i) if(filename[i]=='.') filename[i]='/';
				fileList.emplace(FileInfo{source_path+"/"+filename,0});
			}
		}
	}
}
void LoadConfig()
{
	Config config("/etc/dsa.conf");
	frame = config.pInt("frame");
	max_upload = config.pInt("max_upload");
	timeout = config.pString("timeout");
	testcase_path = config.pString("testcase_path");
	log_path = config.pString("log_path");
	lock_path = config.pString("lock_path");
	source_path = config.pString("source_path");
	upload_path = config.pString("upload_path");
	testcase_num = config.pInt("testcase_num");
	testcase_weight = new int[testcase_num];
	for (int i = 0; i < testcase_num; i++)
	{
		testcase_weight[i] = config.pInt("testcase" + to_string(i) + "_weight");
		cout << testcase_weight[i] << "  ";
	}
	
}
int main()
{
	LoadConfig();
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
		usleep(frame*1000);
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