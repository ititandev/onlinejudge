#include "xmlMake.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "rapidxml.hpp"

using namespace rapidxml;
using namespace std;

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
