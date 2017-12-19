/*
*Chua mot so ham tien ich nhu giai nen, lay thoi gian
*/
#ifndef MY_UTILITY_H
#define MY_UTILITY_H
#include <string>
#include "../include/unzipper.h"
//giai nen @filename va di chuyen noi dung giai nen vao thu muc @destination
bool Unzip(const std::string& filename, const std::string& destination);
//chuyen doi thoi gian lan ghi cuoi cua 1 file thanh dang so nguyen 
long getTimeStamp(const std::string& path);


#endif