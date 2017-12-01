#ifndef _export_h_
#define _export_h_
#include "pugixml.cpp"
#include <string>
using namespace std;
using namespace pugi;
class WriteScore
{
	xml_document doc;
	static WriteScore* s_instance;
	WriteScore();
	public:
	string getFilename();
	static WriteScore* instance();
	void Write(const string& mssv, const string& diem, const string& datetime);
	void saveToFile(const string& filename);
};

#endif