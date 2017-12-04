#include "File.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "pugixml.cpp"
#include "xmlMake.h"
using namespace std;
using namespace pugi;
namespace fs=boost::filesystem;

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
			if(string(child.name())=="dependency") output+=fs::path(child.text().get()).stem().string()+".o:"+child.text().get()+"\n";
			output+=string("\tg++ -c ")+child.text().get()+"\n";
		}
		/*
		output+=string(target.attribute("name").value())+string(":");
		vector<string> depend;
		vector<string> link;
		for(auto& child : target)
		{
			if(string(child.name())=="dependency")
			{
				output+=string(" ")+fs::path(child.text().get()).stem().string()+string(".o");
				depend.push_back(fs::path(child.text().get()).stem().string());
			}
			else if(string(child.name())=="link") link.push_back(child.text().get());
		}
		output+="\n";
		output+="\tg++ ";
		for(auto& dep:depend) output+=dep+".o ";
		for(auto& li:link) output+=li+" ";

		if(target.attribute("type").value()==string("output")) output+="-o ";
		else if(target.attribute("type").value()==string("object")) output+="-c ";
		/*
		output+=" "+string(target.attribute("name").value());
		output+="\n";
		for(auto& dep:depend)
		{
			output+=fs::path(dep).stem().string()+string(".o: ")+dep+string("\n");
			output+="\tg++ -c "+dep+".cpp"+"\n";
		}
		
		for(auto& child:target)
		{
			if(string(child.name())=="dependency")
			{
				output+="\n";
				output+=fs::path(child.value()).stem().string()+":"+child.value()+"\n";
				output+=string("\tg++ -c ")+child.value();
			}
		}
*/
	
	}

	f<<output;
	f.close();
}
//int main()
//{
//	createMakeFile("./");
//}
void createBuildXml(const string& dir)
{ 
	xml_document doc;
	doc.append_child(node_declaration).append_attribute("version")="1.0"; 
	doc.append_child(node_declaration).append_attribute("encoding")="UTF-8";
	auto root=doc.append_child("project");
	auto parrent=root.append_child("target");
	vector<string> sources=Directory(dir).getListFileWithExtension(".cpp");
	for(auto& i:sources)
	{
		parrent.append_child("dependency").text().set(i.c_str());
	}
	doc.save_file((dir+"/pro.xml").c_str());
	
}

/*




}
void createMakefile(const string& dir)
{
	xml_document<> doc;
	ifstream theFile (dir+"/pro.xml");
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	doc.parse<0>(&buffer[0]);
	xml_node<> *node=doc.first_node();
	fstream f(dir+"/Makefile",ios::out);
	while(node!=0)
	{
		if(string(node->name())=="variables")
		{
			f<<node->first_attribute()->value()<<"=";
			f<<node->value()<<"\n";
		}
		else
		{
			if(string(node->name())=="target")
			{
				xml_attribute<> *attr=node->first_attribute();
				string name=attr->value();
				attr=attr->next_attribute();
				string type=attr->value();
				xml_node<>* child=node->first_node();
				string depend;
				string link;
				while(child)
				{
					if(string(child->name())=="dependency")
					{
						attr=child->first_attribute();
						if(attr)
						{
							if(string(attr->value())=="var") link+=string(" ${")+string(child->value())+string("}");
						}
						else
						depend=depend+" "+child->value();
					}
					child=child->next_sibling();
				}
				f<<name<<": ";
				f<<depend<<"\n";
				f<<"\t";
				if(type=="output") f<<"g++ "<<depend<<" "<<link<<" -o "<<name<<endl;
				else f<<"g++ -c "<<depend<<endl;
			}
		}	
		node=node->next_sibling();
	}
}
*/
