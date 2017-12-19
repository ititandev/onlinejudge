#include "../include/Resource.h"
#include "../include/FileProcess.h"
#include "../include/MyException.h"
#include "../include/MyLog.h"
#include "../include/MyUtility.h"
#include "../include/xmlProcess.h"
#ifndef USE_BOOST
#include <regex>
#else
#include <boost/regex.hpp>
using namespace boost;
#endif
#include <fstream>
#include <iostream>

using namespace std;

static Resource::Data Resource::data;
enum LogLevel { LOG_QUIET, LOG_ERROR, LOG_INFO, LOG_DEBUG };

extern LogLevel logLevel;

#define logError(A) ((logLevel >= LOG_ERROR)?((A),0):(0))
#define logInfo(A) ((logLevel >= LOG_INFO)?((A),0):(0))
#define logDebug(A) ((logLevel >= LOG_DEBUG)?((A),0):(0))

void debugBreak();

LogLevel logLevel = LOG_INFO;

Resource::Config::Config(string name, string parentDebugInfo) {
	debugInfo = parentDebugInfo + ", " + name;
}

Resource::Config::Config(string configFile) {
	/*while (*envp) {
		string envEntry = *envp;
		size_t pos = envEntry.find('=');
		if (pos != string::npos) {
			string name = envEntry.substr(0, pos);
			string value = envEntry.substr(pos+1, string::npos);
			envSymbols[name] = value;
			logDebug(cout << "environment symbol: '" << name << "' = '" << value << "'" << endl);
		}
		++envp;
	}*/

	debugInfo = configFile;
	groupStack.push_front(this);

	FILE* in = fopen(configFile.c_str(), "r");
	if (!in) {
		cerr << "cannot open input file '" << configFile << "'" << endl;
		exit(2);
	}

	char buff[1024];
	while (fgets(buff, 1024, in)) {

		string line=buff;
		if ( (line.length() > 2) && (line[0] != '#') && (line.find(')') == string::npos) ) {
			string name;
			string value;
			split(line, name, value, '=');

			if (value == "(") {
				logDebug(cout << "   config: new group '" << name << "'" << endl);
				Config* newGroup = new Config(name, debugInfo);
				groupStack.front()->groups[name] = newGroup;
				groupStack.push_front(newGroup);
			} else {
				for (list<Config*>::reverse_iterator i = groupStack.rbegin(); i != groupStack.rend(); ++i) {
					(*i)->symbolExpand(value);
				}
				envSymbolExpand(value);
				logDebug(cout << "   config: name = '" << name << "', value = '" << value << "'" << endl);
				groupStack.front()->add(name, value);
			}
		}
		if ( (line.length() > 0) && (line[0] != '#') && (line.find(')') != string::npos) ) {
			logDebug(cout << "   end of group" << endl);
			groupStack.pop_front();
		}
	}

	fclose(in);
}

Resource::Config::~Config() {
	for (map<string, Config*>::iterator i = groups.begin(); i != groups.end(); ++i) {
		delete i->second;
	}
}

void Resource::Config::add(string name, string value) {
	symbols[name] = value;
}

void Resource::Config::split(string in, string& left, string& right, char c) {
	size_t pos = in.find_first_of(c);
	if(pos == string::npos) {
		left = in;
		trim(left);
		right = "";
	} else if (pos <= 1) {
		left = "";
		right = in.substr(pos+1, string::npos);
		trim(right);
	} else {
		left = in.substr(0, pos-1);
		trim(left);
		right = in.substr(pos+1, string::npos);
		trim(right);
	}
}

void Resource::Config::trim(string& s) {
	while ( (s.length() > 1) && ( (s[0] == ' ') || (s[0] =='\t') ) ) {
		s = s.substr(1, string::npos);
	}
	while ( (s.length() > 1) &&
			( (s[s.length()-1] == ' ') ||
			  (s[s.length()-1] == '\t') || 
			  (s[s.length()-1] == '\n') || 
			  (s[s.length()-1] == '\r') ) ) {
		s = s.substr(0, s.length()-1);
	}
	if ( (s.length() > 1) && (s[0] == '"') ) {
		s = s.substr(1, string::npos);
	}
	if ( (s.length() > 1) && (s[s.length()-1] == '"') ) {
		s = s.substr(0, s.length()-1);
	}
}

void Resource::Config::symbolExpand(string& s) {
	symbolExpand(symbols, s);
}

void Resource::Config::envSymbolExpand(string& s) {
	symbolExpand(envSymbols, s);
}

void Resource::Config::symbolExpand(map<string, string>& symbols, string& s) {
	bool expanded;
	do {
		expanded = false;
		for (map<string, string>::iterator i = symbols.begin(); i != symbols.end(); ++i) {
			string search = "%" + i->first + "%";
			string replace = i->second;
			size_t pos = s.find(search);
			if (pos != string::npos) {
				expanded = true;
				s.replace(pos, search.length(), replace);
			}
		}
	} while (expanded);
}

string Resource::Config::pString(string name) {
	map<string, string>::iterator i = symbols.find(name);
	if (i == symbols.end()) {
		logError(cout << "access of missing property '" << name << "' (" << debugInfo << ")" << endl);
		exit(4);
	}
	return i->second;
}

bool Resource::Config::pBool(string name) {
	string val = pString(name);

	if ( (val == "yes") ||
	     (val == "Yes") ||
	     (val == "YES") ||
		 (val == "true") ||
	     (val == "True") ||
	     (val == "TRUE"))
	{
		return true;
	}

	return false;
}

double Resource::Config::pDouble(string name) {
	string val = pString(name);

	return atof(val.c_str());
}

int Resource::Config::pInt(string name) {
	string val = pString(name);

	return atoi(val.c_str());
}

Resource::Data::Data()
{
	config_path="/etc/onlinejudge";
	auto file = File(config_path+"/onlinejudge.conf");
	if (!file.isFileExist())
	{
		SystemLog::instance()->WriteToFile("Not found config file at '"+config_path+"/onlinejudge.conf'");
		exit(1);
	}
	Config config(config_path+"/onlinejudge.conf");
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
		auto file = File(config_path+"/" + ass_name[i] + ".conf");
		if (!file.isFileExist())
		{
			SystemLog::instance()->WriteToFile("Not found config file for " + ass_name[i] + " at '"+config_path+"/" + ass_name[i] + ".conf'");
			exit(1);
		}
		Config config(config_path+"/" + ass_name[i] + ".conf");
		ass_config[i].timeout = config.pString("timeout");
		ass_config[i].testcase_path = config.pString("testcase_path");
		ass_config[i].testcase_num = config.pInt("testcase_num");
		ass_config[i].xml_yes = config.pString("xml_yes");
		ass_config[i].xml_no = config.pString("xml_no");
		ass_config[i].xml_path = config.pString("xml_path");
		ass_config[i].output_format = config.pString("output_format");
	}
	//check folder is exist, if not create them
	Directory::create(upload_path);
	for (int i = 0; i < ass_num; i++)
	{
		Directory::create(upload_path + "/" + ass_name[i]);
		Directory::create(source_path + "/" + ass_name[i]);
	}
	Directory::create(lock_path);
}

Resource::Data::~Data()
{
	delete [] ass_name;
	delete [] ass_config;
}
static int& Resource::frame()
	{
		return data.frame;
	}
static string& Resource::lock_path()
	{
		return data.lock_path;
	}
static string& Resource::source_path()
	{
		return data.source_path;
	}
static string& Resource::upload_path()
	{
		return data.upload_path;
	}
static string& Resource::config_path()
	{
		return data.config_path;
	}
static int& Resource::ass_num()
	{
		return data.ass_num;
	}
static string& Resource::ass_name(int i)
	{
		return data.ass_name[i];
	}
static ass_config_t& Resource::ass_config(int i)
	{
		return data.ass_config[i];
	}
bool operator<(const FileInfo& lhs,const FileInfo& rhs)
{
	return lhs.timeStamp > rhs.timeStamp;
}








/*
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
void Execute(FileInfo& fileInfo)
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
*/
