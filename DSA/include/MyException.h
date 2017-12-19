#ifndef MYEXCEPTION_H_
#define MYEXCEPTION_H_
#include <exception>
#include <string>
//Tao mot lop ke thua tu lop exception de quan ly cac ngoai le chuong trinh
//Ham tao cua lop nhan chuoi thong bao loi
//Ham what se xuat thong bao loi cua chuong trinh
class MyException:public std::exception
{
private:
	std::string warning;
public:
	MyException(const std::string& warning)
	{
		this->warning = warning;
	}
	const char* what() const noexcept
	{
		return warning.c_str();
	}
};
#endif