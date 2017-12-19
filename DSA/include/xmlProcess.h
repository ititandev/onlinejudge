/*
*Chua cac ham nhap xuat xml
*/
#ifndef _xmlProcess_H_
#define _xmlProcess_H_
#include <string>
#include "pugixml.hpp"
#include <string>
using namespace std;
using namespace pugi;
//Tao ra Makefile cho 1 project chua trong thu muc @dir
void createMakeFile(const std::string& dir);
//Tao ra build xml cho 1 project chua trong thu muc @dir
void createBuildXml(const std::string& dir);
//Lop quan ly viec xuat ket qua cham diem ra file xml
class WriteScore
{
	xml_document doc;
	static WriteScore* s_instance;
	WriteScore();
	public:
	string getFilename();
	static WriteScore* instance();
	void Write(const std::string& mssv, const std::string& diem, const std::string& datetime);
	void saveToFile(const std::string& filename);
};

#endif
