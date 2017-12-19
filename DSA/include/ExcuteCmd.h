/*
*Chua cac ham xu ly viec thuc thi cac lenh shell duoc goi ben trong chuong trinh c++
*/
#ifndef ExcuteCmd_H
#define ExcuteCmd_H
#include <string>
#include <vector>
#define TIMEOUT -100
#define RUNTIME_ERROR -200
//Thuc thi lenh @cmd va tra ve ket qua thuc thi cua lenh, neu that bai gia tri tra ve la -1
int cmdExec(const std::string& cmd,std::vector<std::string>& params,int timeout=-1, const std::string& fileOut="");

#endif
