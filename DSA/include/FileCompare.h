/*
*Chua ham xu ly viec so sanh noi dung cac file voi nhau
*/
#ifndef FileCompare_H
#define FileCompare_H
#include <fstream>
//So sanh noi dung cua 2 file @in1, @in2 theo cach so trung tung byte
bool equalFiles(std::ifstream& in1, std::ifstream& in2);

#endif 
