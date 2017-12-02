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

struct ass_config_t
{
	string timeout;
	int testcase_num;
	string testcase_path;
};

int frame;
string lock_path;
string source_path;
string upload_path;
int ass_num;
string *ass_name;
ass_config_t *ass_config;

void LoadConfig()
{
	auto file = File("/etc/onlinejudge/onlinejudge.conf");
	if (!file.isFileExist())
	{
		cout << "Not found config file at '/etc/onlinejudge/onlinejudge.conf'";
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
			cout << "Not found config file for " + ass_name[i] + " at '/etc/onlinejudge/" + ass_name[i] + ".conf'";
			exit(1);
		}
		Config config("/etc/onlinejudge/" + ass_name[i] + ".conf");
		ass_config[i].timeout = config.pString("timeout");
		ass_config[i].testcase_path = config.pString("testcase_path");
		ass_config[i].testcase_num = config.pInt("testcase_num");
	}
}

void writeLog(string str)
{
	fstream log("/etc/onlinejudge/log.log", ios_base::app);
	log << str << endl;
	log.close();
	cout << str << endl;
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


class MyException :public exception
{
private:
	string text;
public:
	MyException(const string& str)
	{
		text = str;
	}
	MyException()
	{
		text = "";
	}
	char const* what() const throw()
	{
		return text.c_str();
	}
};

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
			throw MyException("invalid format file name " + filename);
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
void Compile(FileInfo& submit, const string& logfile)
{
	createMakefile(submit.path);
	string cmd2 = "cd " + submit.path + "; make";
	bool succ;
	Run(cmd2, succ, logfile);
	if (!succ)
	{
		throw MyException();
	}
}
void Run(FileInfo& submit)
{
	try
	{
		string& pathToSubmit = submit.path;
		string remove = "rm -f " + pathToSubmit + "/*.out";
		system(remove.c_str());
		for (size_t i = 0; i < ass_config[submit.ass_num].testcase_num; i++)
		{
			string command = "timeout " + ass_config[submit.ass_num].timeout + " " + pathToSubmit + "/program ";
			string param = ass_config[submit.ass_num].testcase_path + "/" + to_string(i) + ".in " + pathToSubmit + "/" + to_string(i) + ".out";

			system((command + param + " ; if [ $? -eq 124 ]; then echo \"Timeout error\";fi" + " &>> " + getLogFile(pathToSubmit)).c_str());
			//Ghi vo log chinh va xoa log tam.... ben toi File.h bi loi
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
				ss += "Pass\n";
				pass_num++;
			}
			else
				ss += "Fail\n";
		}
		file << "Score: " << endl << fixed  << setprecision(1) << (float) pass_num / ass_config[submit.ass_num].testcase_num *10 << endl;
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
		score << "Score:\t\t\t0\n";
		score.close();
		string filename = getLogFile(submitPath);
		fstream f(filename, ios::out | ios::app);
		f << e.what();
		f.close();
		File(filename).moveTo(submitPath + "/log.txt");
	}
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
			cout << e.what();
			writeLog(e.what());
		}
		catch (...)
		{
			cout << "Unexpected error occurs...";
		}
	}
}
