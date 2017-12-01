//#include "pugixml.hpp"
#include "export.h"
#include <chrono>
#include <time.h>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <sstream>
#include <fstream>
#include "File.h"
using namespace std;
using namespace pugi;
using namespace std::chrono_literals;
WriteScore::WriteScore()
	{
		doc.append_child(node_declaration).append_attribute("version")="1.0";  
		doc.root().set_name("table");
	}

static WriteScore* WriteScore::instance() 
	{
		if(!s_instance)
			s_instance=new WriteScore;
		return s_instance;
	}
void WriteScore::Write(const string& mssv, const string& diem, const string& datetime)
	{
		auto root=doc.append_child("record");
		root.append_child("MSSV").text().set(mssv.c_str());
		root.append_child("Diem").text().set(diem.c_str());
		root.append_child("TimeSubmit").text().set(datetime.c_str());
	}
void WriteScore::saveToFile(const string& filename)
	{
		doc.save_file(filename.c_str());
	}
	WriteScore* WriteScore::s_instance=NULL;
string getDateTime(const string& p)
{
	auto t=fs::last_write_time(p);
	char buff[100];
	time_t cftime=chrono::system_clock::to_time_t(t);
	strftime(buff,100,"%H:%M:%S %d/%m/%Y",localtime(&cftime));
	return string(buff,buff+100);

}
int main()
{
	string dirPath="/home/tuankiet/public_html/Source";
	vector<string> lst=Directory(dirPath).getListDirectory();
	for(auto& i: lst)
	{
		vector<string> sublst=Directory(i).getListDirectory();
		for(auto& p:sublst)
		{
			fstream f(p+"/score.log",ios::in);
			string tmp;
			int score;
			f>>tmp>>score;
			string ms=File(i).getFilename();
			string date=getDateTime(p);
			WriteScore::instance()->Write(ms,to_string(score),date);
		}
	}
	WriteScore::instance()->saveToFile("score.xml");
}

