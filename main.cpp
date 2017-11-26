#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

#include "config.h"

int main(int argc, char* argv[], char* envp[])
{
	Config config("config.txt", NULL);


	cout << "frame    = '" << config.pInt("frame") << "'" << endl;
	cout << "max_upload = '" << config.pInt("max_upload") << "'" << endl;
	cout << "timeout = '" << config.pInt("timeout") << "'" << endl;
	cout << endl;
	system("pause");
	return 0;
}

