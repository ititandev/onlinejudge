#include "../include/xmlProcess.h"
#include "../include/FileProcess.h"
#include "../include/pugixml.hpp"
#include <stdio.h>
#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
using namespace pugi;

void createMakeFile(const string& dir)
{
	string filename=dir+"/pro.xml";
	xml_document doc;
	xml_parse_result result=doc.load_file(filename.c_str(),parse_default|parse_declaration);
	if(!result)
	{
		throw string("Failed to parse xml file");
	}
	auto root=doc.document_element();
	
	fstream f(dir+"/Makefile",ios::out);
	string output;
	for(auto& target: root.children())
	{
		if(string(target.attribute("type").value())=="output")
		{
			vector<string> dep;
			output+=string(target.attribute("name").value())+": ";
			for(auto& child:target)
			{
				if(string(child.name())=="dependency") dep.push_back(fs::path(child.text().get()).stem().string()+".o ");
			}
			for(auto& i:dep) output+=i;
			output+="\n";
			output+="\tg++ ";
			for(auto& i:dep) output+=i;
			output+=string(" -o ")+target.attribute("name").value()+"\n";
			
		}
		else
		{
			vector<string> dep;
			output+=string(target.attribute("name").value())+".o: ";
			for(auto& child:target)
			{
				if(string(child.name())=="dependency") dep.push_back(fs::path(child.text().get()).stem().string()+".cpp ");
			}
			for(auto& i:dep) output+=i;
			output+="\n";
			output+="\tg++ -c";
			for(auto& i:dep) output+=i;
		}
		for(auto& child:target)
		{
			if(string(child.name())=="dependency") 
			{		
				output+=fs::path(child.text().get()).stem().string()+".o:"+child.text().get()+"\n";
				output+=string("\tg++ -c ")+child.text().get()+"\n";
			}
		}
	
	}

	f<<output;
	f.close();
}

void createBuildXml(const string& dir)
{ 
	xml_document doc;
	auto dec=doc.append_child(node_declaration).append_attribute("version")="1.0"; 
	auto root=doc.append_child("project");
	auto parrent=root.append_child("target");
	parrent.append_attribute("name").set_value("program");
	parrent.append_attribute("type").set_value("output");
	vector<string> sources=Directory(dir).getListFileWithExtension(".cpp");
	for(auto& i:sources)
	{
		parrent.append_child("dependency").text().set(File(i).getFilename().c_str());
	}
	doc.save_file((dir+"/pro.xml").c_str());
	
}

WriteScore::WriteScore()
	{
		doc.append_child(node_declaration).append_attribute("version")="1.0";  
		doc.append_child("table");
	}

static WriteScore* WriteScore::instance() 
	{
		if(!s_instance)
			s_instance=new WriteScore;
		return s_instance;
	}
void WriteScore::Write(const string& mssv, const string& diem, const string& datetime)
	{
		auto root=doc.child("table");
		auto parent=root.append_child("record");
		parent.append_child("MSSV").text().set(mssv.c_str());
		parent.append_child("Diem").text().set(diem.c_str());
		parent.append_child("TimeSubmit").text().set(datetime.c_str());
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
#ifndef USE_BOOST
	time_t cftime=std::chrono::system_clock::to_time_t(t);
#else
	time_t cftime=t;
#endif
	strftime(buff,100,"%H:%M:%S %d/%m/%Y",localtime(&cftime));
	return string(buff,buff+100);

}
/*
int main(int argv, char** args)
{
	if(argv==2)
	{
	string dirPath=string("/home/tuankiet/public_html/Source/")+args[1];
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
}
*/
