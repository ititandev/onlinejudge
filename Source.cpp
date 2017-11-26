
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
using namespace std;
#include "config.h"
#include "equalFiles.h"

int frame, max_upload;
string timeout;
string testcase_path;
int testcase_num;
string log_path;

void Run(string& pathToSubmit)
{
	string command = "timeout " + timeout + " g++ -o program " + pathToSubmit + "*.cpp"; 
		cout << command;
	system(command.c_str());
}
void Mark(string& pathToSubmit)
{

}

int main(int argc, char* argv[], char* envp[])
{
	Config config("config.txt");
	frame = config.pInt("frame");
	max_upload = config.pInt("max_upload");
	timeout = config.pString("timeout");
	testcase_path = config.pString("testcase_path");
	testcase_num = config.pInt("testcase_num");
	log_path = config.pString("log_path");

	/*cout << "frame    = " << frame << endl;
	cout << "max_upload = " << max_upload << endl;
	cout << "timeout = " << timeout << endl;*/
	string path = "./";
	//Run(path);
	cout << endl;
	return 0;
}

