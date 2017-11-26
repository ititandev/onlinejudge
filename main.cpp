#include "File.h"
#include "exec.h"
#include <exception>
#include <thread>
#include <string>
#include <iostream>
#include <cstdlib>
#include <queue>
#include <fstream>
#include <regex>
#include "chilkat/include/CkZip.h"


string uploadPath="/home/tuankiet/Project/Upload";
string lockPath="/home/tuankiet/Project/lock";
string sourcePath="/home/tuankiet/Project/Source";
queue<string> sources;



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


bool Unzip(const string& filename, const string& directory)
{
    try
    {
        CkZip zip;
        bool success;

        success = zip.UnlockComponent("Anything for 30-day trial");
        if (success != true) return false;

        success = zip.OpenZip(filename.c_str());
        if (success != true) {
            return false;
        }
        int unzipCount;
        unzipCount = zip.Unzip(directory.c_str());
        if (unzipCount < 0) {
        return false;
        }
        else    {
            return true;
        }
    }
    catch(exception& e)
    {
        throw;
    }
}


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

void preparequeue()
{
    try
    {
	Directory dir(uploadPath);
	vector<string> lst=dir.getListFile();
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
		sources.push(dirPath);
		File(i).deleteFile();
	}
    }
    catch(exception& e)
    {
        throw;
    }
}

string Run(const string& cmd, bool& success)
{
    try
    {
    string com=cmd+" &> tmp.txt";
    int succ=system(com.c_str());
    fstream f("tmp.txt",ios::in);
    string output;
    string tmp;
    while(!f.eof())
    {
        getline(f,tmp);
        output+=tmp+"\n";
    }
    success=(succ==0);
    return output;
    }
    catch(exception& e)
    {
        File("tmp.txt").deleteFile();
        throw;
    }
}

void compile(const string& dir)
{
    try
    {
	string cmd2="g++ -o program "+dir+"/"+"*.cpp";
        bool succ;
        string str=Run(cmd2,succ);
	    if(!succ)
	    {
		    throw MyException(str);
	    }
    }
    catch(exception& e)
    {
	    string filename=lockPath+string("/")+File(Directory(dir).getParentDirectory()).getFilename()+string(".")+File(dir).getFilename()+string(".log");
        fstream f(filename,ios::out);
	    f<<e.what();
	    f.close();
	    File(filename).moveTo(dir+File(filename).getFilename());
    }
}
int main()
{
	try
	{
		preparequeue();
		vector<thread> arrThread;
		while(!sources.empty())
		{
			string dir=sources.front();
			sources.pop();
			arrThread.push_back(thread(compile,dir));

		}
		for(int i=0;i<arrThread.size();++i) arrThread[i].join();
	}
	catch(exception& e)
	{
		cout<<e.what();
	}
	catch(string& s)
	{
		cout<<s;
	}
}
