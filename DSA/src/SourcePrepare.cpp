#include "../include/SourcePrepare.h"
#include <iostream>
#include <boost/regex.hpp>
#include "../include/MyException.h"
#include "../include/MyLog.h"
#include "../include/MyUtility.h"
#include "../include/ExcuteCmd.h"
using namespace std;
SourcePrepare::SourcePrepare()
{}
static SourcePrepare SourcePrepare::s_instance;
static SourcePrepare& SourcePrepare::instance()
{
	return s_instance;
}
bool SourcePrepare::isSourceEmpty()
{
	return fileList.empty();
}
FileInfo SourcePrepare::getSourceInfo()
{
	FileInfo f=fileList.top();
	fileList.pop();
	return f;
}
//Format log file to recover: [ass_name].[mssv].[index]
void SourcePrepare::Recover()
{

	string path = Resource::lock_path();
	vector<string> lst = Directory(path).getListFile();

	if (lst.size() > 0)
	{
		cout << "Found lock file in lock directory\n";
		cout << "Do you want to recover last sesion(Y/N): ";
		string str;
		getline(cin, str);
		while (str != "Y"&&str != "N"&&str != "y"&&str != "n")
		{
			cout << "Input error, try again!\n";
			getline(cin, str);
		}
		if (str == "n" || str == "N")
		{
			cout << "Don't recover last session, removing the lock files.....\n";
			for (auto& p : lst) File(p).deleteFile();
		} 
	else
	{

		cout << "Recovering the last session.....\n";
		for (auto& p : lst)
		{
			string filename = File(p).getFilename();
			for (int i = 0; i < filename.size(); ++i) if (filename[i] == '.') filename[i] = '/';
			string assname;
			for(int i=0;filename[i]!='/';++i) assname+=filename[i];
			int i=0;
			for(;i<Resource::ass_num();++i) if(Resource::ass_name(i)==assname) break;
			if(i==Resource::ass_num())
			{
				cout<<"Invalid format lock file!....";
				return;
			} 
			string cmd="/usr/bin/rm";
			vector<string> params;
			params.push_back("-rf");
			params.push_back(Resource::source_path()+"/"+filename+"/log.txt");
			params.push_back(Resource::source_path()+"/"+filename+"/program");
			cmdExec(cmd,params);
			string dir=Resource::source_path() + "/" + filename;
			fileList.emplace(FileInfo{dir ,getTimeStamp(dir), i });
		}
		cout << "Recover done....\n";
		cout << "Continue new session.....\n";
	}
}
}

string SourcePrepare::getFolder(const string& path, const string& ass_name)
{
	try
	{
		boost::regex r("([0-9]*)_([0-9]*)");
		boost::smatch m;
		string name;
		string filename = File(path).getFilenameOnly();
		if (boost::regex_match(filename, m, r))
		{
			name = m[1];
		}
		else
		{
			File(path).deleteFile();
			throw MyException("Delete " + path + "because invalid format file name ");
		}
		string parent = Directory(path).getParentDirectory();
		int index = Directory(Resource::source_path() + "/" + ass_name + "/" + name).directoryCount() + 1;
		return name + "/" + to_string(index);
	}
	catch (exception& e)
	{
		throw;
	}
}
void SourcePrepare::LoadSource()
{
	
	for (int i = 0; i < Resource::ass_num(); i++)
	{
		string path = Resource::upload_path() + "/" + Resource::ass_name(i);
		Directory dir(path);
		vector<string> listFile = dir.getListFile();

		if (listFile.size() == 0)
			continue;
		for (auto& filePath : listFile)
		{
			try
			{
				string desPath;
				desPath = Resource::source_path() + "/" + Resource::ass_name(i) + "/" + getFolder(filePath, Resource::ass_name(i));

				if (!Directory::create(desPath))
					throw MyException("Can't create directory " + desPath);
				if (!Unzip(filePath, desPath))
					throw MyException("Unzip error filename: " + desPath);
				else
				{
					SystemLog::instance()->WriteToFile("Move " + filePath + " to " + desPath);
					/*
					fstream f(getLogFile(desPath), ios::out | ios::app);
					f.close();
					*/
				}
				fileList.emplace(FileInfo{ desPath,getTimeStamp(filePath), i });
				File(filePath).deleteFile();
			}
			catch (exception& e)
			{
				SystemLog::instance()->WriteToFile(e.what());
			}
		}
	}
}