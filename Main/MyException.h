#ifndef MYEXCEPTION_H_
#define MYEXCEPTION_H_
#include <exception>
#include <string>
using namespace std;
class MyException:public exception
{
private:
	string warning;
public:
	MyException(const string& warning)
	{
		this->warning = warning;
	}
	const char* what() const noexcept
	{
		return warning.c_str();
	}
};
#endif