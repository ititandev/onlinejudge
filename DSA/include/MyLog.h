#ifndef LOG_H
#define LOG_H
#include <fstream>
#include <iostream>
#include <string>
#include "../include/Resource.h"
//Header chua cac lop lien quan toi viec ghi lai log cua he thong khi lam viec
//Bao gom 2 lop: SystemLog va StudentLog
//@SystemLog: ghi lai log khi phan mem chay
//@StudentLog: ghi lai log khi thuc hien cham bai tung sinh vien

//Class ho tro viec ghi lai log khi he thong lam viec
//Implement theo pattern Singleton de dam bao chi co 1 the hien cua lop khi chuong trinh chay

class SystemLog
{
private:
	static SystemLog* s_instance;
	std::fstream log;
	SystemLog();
public:
	static SystemLog* instance();
	//Dat lai duong dan file log he thong
	//Ham nay neu duoc goi phai la ham duoc goi dau tien
	//@append: ho tro che do ghi de neu duoc set @true, nguoc lai tao file moi
	void setLogFile(const std::string& fileLog, bool append=true);
	//Ghi log ra console
	void WriteToConsole(const std::string& str);
	//Ghi log ra file log, mac dinh: /etc/onlinejudge/log.log, hoac duoc set boi @setLogFile
	//debug=true ho tro ghi them ra man hinh ho tro cho viec debug
	void WriteToFile(const std::string& str,bool debug=true);
	~SystemLog();
};

//Class ho tro viec ghi lai log file trong qua trinh cham diem cua sinh vien
//Khi bat dau goi ham CRM::Execute(), class bat dau qua trinh ghi log
//Class se tao ra mot file log nam trong thu muc @lock co dang: [ass_name].[mssv].[index].log
//Neu khong xay ra loi he thong trong qua trinh compile-run-mark point, class se chuyen file tren
//sang thu muc hien hanh cua sinh vien dang duoc cham diem va doi ten thanh log.txt, se khong lam gi
//neu co loi xay ra
class StudentLog
{
private:
	std::fstream log;
	std::string filename;
public:

	StudentLog(const FileInfo& fileInfo);
	void WriteToConsole(const std::string& log);
	void WriteToFile(const std::string& str);
	std::string getFilePath();
	~StudentLog();
};
#endif
