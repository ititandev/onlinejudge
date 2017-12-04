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
#include <iomanip>
#include <cstdlib>
#include <queue>
#include <fstream>
#include <unistd.h>
#include <boost/regex.hpp>
#include "outputformat.cpp"
#include "MyException.h"
#include <time.h>
#include <stdio.h>

struct ass_config_t
{
	string timeout;
	int testcase_num;
	string testcase_path;
	string xml_yes;
	string xml_no;
	string xml_path;
	string output_format;
};

int frame;
string lock_path;
string source_path;
string upload_path;
int ass_num;
string *ass_name;
ass_config_t *ass_config;

void writeLog(string str)
{
	fstream log("/etc/onlinejudge/log.log", ios_base::app);
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

	log << string(buf) << " " << str << endl;
	log.close();
	cout << str << endl;
}

void LoadConfig()
{
	auto file = File("/etc/onlinejudge/onlinejudge.conf");
	if (!file.isFileExist())
	{
		writeLog("Not found config file at '/etc/onlinejudge/onlinejudge.conf'");
		exit(1);
	}
	Config config("/etc/onlinejudge/onlinejudge.conf");
	frame = config.pInt("frame");
	lock_path = config.pString("lock_path");
	source_path = config.pString("source_path");
	upload_path = config.pString("upload_path");
	ass_num = config.pInt("ass_num");
	ass_name = new string[ass_num];
	for (int i = 0; i < ass_num; i++)
		ass_name[i] = config.pString("ass" + to_string(i) + "_name");

	//Read config each assignment
	ass_config = new ass_config_t[ass_num];
	for (int i = 0; i < ass_num; i++)
	{
		auto file = File("/etc/onlinejudge/" + ass_name[i] + ".conf");
		if (!file.isFileExist())
		{
			writeLog("Not found config file for " + ass_name[i] + " at '/etc/onlinejudge/" + ass_name[i] + ".conf'");
			exit(1);
		}
		Config config("/etc/onlinejudge/" + ass_name[i] + ".conf");
		ass_config[i].timeout = config.pString("timeout");
		ass_config[i].testcase_path = config.pString("testcase_path");
		ass_config[i].testcase_num = config.pInt("testcase_num");
		ass_config[i].xml_yes = config.pString("xml_yes");
		ass_config[i].xml_no = config.pString("xml_no");
		ass_config[i].xml_path = config.pString("xml_path");
	}
}
void checkFolder()
{

	Directory::create(upload_path);
	for (int i = 0; i < ass_num; i++)
	{
		Directory::create(upload_path + "/" + ass_name[i]);
		Directory::create(source_path + "/" + ass_name[i]);
	}
	Directory::create(lock_path);
}
struct FileInfo
{
	string path;
	long timeStamp;
	int ass_num;
};
bool operator<(const FileInfo& op1, const FileInfo& op2)
{
	return op1.timeStamp > op2.timeStamp;
}
string getLogFile(const string& dir)
{
	return lock_path + "/" + File(Directory(dir).getParentDirectory()).getFilenameOnly() + "." + File(dir).getFilename() + ".log";
}
priority_queue<FileInfo> fileList;

string getFolder(const string path, string ass_name)
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
		int index = Directory(source_path + "/" + ass_name + "/" + name).dirsCount() + 1;
		return name + "/" + to_string(index);
	}
	catch (exception& e)
	{
		throw;
	}
}

void addFileList()
{
	for (int i = 0; i < ass_num; i++)
	{
		string path = upload_path + "/" + ass_name[i];
		Directory dir(path);
		vector<string> listFile = dir.getListFile();
		if (listFile.size() == 0) return;
		for (auto& filePath : listFile)
		{
			string desPath;
			try
			{
				desPath = source_path + "/" + ass_name[i] + "/" + getFolder(filePath, ass_name[i]);
			}
			catch (exception& e)
			{
				writeLog(e.what());
				continue;
			}
			if (!Directory::create(desPath))
				throw MyException("Can't create directory " + desPath);
			if (!Unzip(filePath, desPath))
				throw MyException("Unzip error filename: " + desPath);
			else
			{
				writeLog("Move " + filePath + " to " + desPath);
				fstream f(getLogFile(desPath), ios::out | ios::app);
				f.close();
			}
			fileList.emplace(FileInfo{ desPath,getTimeStamp(filePath), i });
			File(filePath).deleteFile();
		}
	}
}


void CreateXML(FileInfo& submit)
{
	if (File(submit.path + "/pro.xml").isFileExist())
	{
		string& config = ass_config[submit.ass_num].xml_yes;
		if (config == "auto")
			createBuildXml(submit.path);
		else if (config == "hard")
		{
			if (!File(submit.path + "/pro.xml").deleteFile())
			{
				writeLog("Error delete " + submit.path + "/pro.xml");
				throw MyException("Error pro.xml");
			}
			File(ass_config[submit.ass_num].xml_path).copyTo(submit.path + "/pro.xml");
			writeLog("Copy " + ass_config[submit.ass_num].xml_path + " to " + submit.path + "/pro.xml");
		}
		else if (config == "keep")
			;
		else if (config == "error")
			throw MyException("Error pro.xml");
		else
		{
			writeLog("Error config xml_yes = '" + config + "'");
			throw MyException("Error pro.xml");
		}
	}
	else
	{
		string& config = ass_config[submit.ass_num].xml_no;
		if (config == "auto")
			createBuildXml(submit.path);
		else if (config == "hard")
		{
			if (!File(submit.path + "/pro.xml").deleteFile())
			{
				writeLog("Error delete " + submit.path + "/pro.xml");
				throw MyException("Error pro.xml");
			}
			File(ass_config[submit.ass_num].xml_path).copyTo(submit.path + "/pro.xml");
			writeLog("Copy " + ass_config[submit.ass_num].xml_path + " to " + submit.path + "/pro.xml");
		}
		else if (config == "error")
			throw MyException("Error pro.xml");
		else
		{
			writeLog("Error config xml_no  = '" + config + "'");
			throw MyException("Error pro.xml");
		}
	}

}
void Compile(FileInfo& submit, const string& logfile)
{
	writeLog("Compiling " + submit.path);
	CreateXML(submit);
	createMakeFile(submit.path);
	string cmd2 = "cd " + submit.path + "; make";
	bool succ;
	Run(cmd2, succ, logfile);
	if (!succ)
	{
		throw MyException("Compile error");
	}
}
void Run(FileInfo& submit)
{
	try
	{
		writeLog("Running " + submit.path);
		string& pathToSubmit = submit.path;
		string remove = "rm -f " + pathToSubmit + "/*.out";
		system(remove.c_str());
		for (size_t i = 0; i < ass_config[submit.ass_num].testcase_num; i++)
		{
			string command = "timeout " + ass_config[submit.ass_num].timeout + " " + pathToSubmit + "/program ";
			string param = ass_config[submit.ass_num].testcase_path + "/" + to_string(i) + ".in " + pathToSubmit + "/" + to_string(i) + ".out";

			system((command + param + " ; if [ $? -eq 124 ]; then echo \"Timeout error\";fi" + " &>> " + getLogFile(pathToSubmit)).c_str());
		}
	}
	catch (exception& e)
	{
		throw;
	}

}

//Tinh diem luu vo score.log
void Mark(FileInfo& submit)
{
	try
	{
		writeLog("Marking " + submit.path);
		string& pathToSubmit = submit.path;
		string remove = "rm -f " + pathToSubmit + "/score.log";
		system(remove.c_str());
		fstream file(pathToSubmit + "/score.log", ios::out);
		int pass_num = 0;
		string ss;
		for (size_t i = 0; i < ass_config[submit.ass_num].testcase_num; i++)
		{
			ss += "Testcase " + to_string(i + 1) + "\n";
			ifstream origin(ass_config[submit.ass_num].testcase_path + "/" + to_string(i) + ".out");
			ifstream compare(pathToSubmit + "/" + to_string(i) + ".out");
			if (equalFiles(origin, compare))
			{
				ss += "Pass";
				pass_num++;
			}
			else
				ss += "Fail";
			if (i < ass_config[submit.ass_num].testcase_num - 1)
				ss += "\n";
		}
		file << "Score: " << endl << fixed << setprecision(1) << (float)pass_num / ass_config[submit.ass_num].testcase_num * 10 << endl;
		file << ss;
		file.close();
	}
	catch (exception& e)
	{
		throw;
	}
}
void Execute(FileInfo fileInfo)
{
	writeLog("Start auto mark for " + fileInfo.path);
	string& submitPath = fileInfo.path;
	int &ass_num = fileInfo.ass_num;
	bool write = false;
	try
	{
		string logfile = getLogFile(submitPath);
		Compile(fileInfo, logfile);
		Run(fileInfo);
		Mark(fileInfo);
		File(logfile).moveTo(submitPath + "/log.txt");
	}
	catch (exception& e)
	{
		fstream score(submitPath + "/" + "score.log", ios::out);
		score << "Score:\n0";
		score.close();
		string filename = getLogFile(submitPath);
		fstream f(filename, ios::out | ios::app);
		f << e.what();
		f.close();
		File(filename).moveTo(submitPath + "/log.txt");
	}
	writeLog("Finish auto mark for " + fileInfo.path);
}
void Recover()
{
	for (int i = 0; i < ass_num; i++)
	{
		string path = lock_path + "/" + ass_name[i];
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
					string filename = File(p).getFilenameOnly();
					for (int i = 0; i < filename.size(); ++i) if (filename[i] == '.') filename[i] = '/';
					fileList.emplace(FileInfo{ source_path + "/" + filename,0, i });
				}
			}
			cout << "Recover done....\n";
			cout << "Continue new session.....\n";
		}
	}
}

int main()
{
	LoadConfig();
	checkFolder();
	Recover();
	while (true)
	{
		try
		{
			addFileList();
			vector<thread> arrThread;
			while (!fileList.empty())
			{
				FileInfo fileInfo = fileList.top();
				fileList.pop();
				arrThread.push_back(thread(Execute, fileInfo));
			}
			for (int i = 0; i < arrThread.size(); ++i) arrThread[i].join();
			usleep(frame * 1000);
		}
		catch (exception& e)
		{
			writeLog(e.what());
		}
		catch (...)
		{
			writeLog("Unexpected error occurs...");
		}
	}
}
