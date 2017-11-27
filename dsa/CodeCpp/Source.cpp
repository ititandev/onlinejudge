
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <string>
#include "config.h"
#include "equalFiles.h"
#include <fstream>
#include <sstream>

using namespace std;
int frame, max_upload;
string timeout;
string testcase_path;
int testcase_num;
int *testcase_weight;
string log_path;
string lock_path;
string source_path;
string upload_path;

void Run(string& pathToSubmit)
{
	string remove = "rm -f " + pathToSubmit + "/*.out";
	system(remove.c_str());
	remove = "rm -f " + pathToSubmit + "/log*";
	system(remove.c_str());

	for (size_t i = 0; i < testcase_num; i++)
	{
		string command = "timeout " + timeout + " ./" + pathToSubmit + "/program ";
		string param = testcase_path + "/" + to_string(i) + ".in " + pathToSubmit + "/" + to_string(i) + ".out";
		//cout << command + param + " &> " + pathToSubmit + "/log" + to_string(i) + ".txt" << endl;
		system((command + param + " &> " + pathToSubmit + "/log" + to_string(i) + ".txt").c_str());
		//Ghi vo log chinh va xoa log tam.... ben to File.h bi loi
	}

}

//Tinh diem luu vo score.log
void Mark(string& pathToSubmit)
{
	string remove = "rm -f " + pathToSubmit + "/score.log";
	system(remove.c_str());
	fstream file(pathToSubmit + "/score.log", ios::out);
	double score = 0;
	string ss;
	for (size_t i = 0; i < testcase_num; i++)
	{
		ss += "Testcase " + to_string(i + 1);
		ifstream origin(testcase_path + "/" + to_string(i) + ".out");
		ifstream compare(pathToSubmit + "/" + to_string(i) + ".out");
		if (equalFiles(origin, compare))
		{
			ss += ": Pass\t";
			ss += to_string(testcase_weight[i]/10) + '\n';
			score += testcase_weight[i];
		}
		else
			ss += ": Fail\t0\n";
	}
	score /= 10;
	file << "Score: \t\t\t" << score << endl;
	file << ss;
	file.close();
}

int main(int argc, char* argv[], char* envp[])
{
	Config config("/etc/dsa.conf");
	frame = config.pInt("frame");
	max_upload = config.pInt("max_upload");
	timeout = config.pString("timeout");
	testcase_path = config.pString("testcase_path");
	log_path = config.pString("log_path");
	lock_path = config.pString("lock_path");
	source_path = config.pString("source_path");
	upload_path = config.pString("upload_path");
	testcase_num = config.pInt("testcase_num");
	testcase_weight = new int[testcase_num];
	for (int i = 0; i < testcase_num; i++)
	{
		testcase_weight[i] = config.pInt("testcase" + to_string(i) + "_weight");
		cout << testcase_weight[i] << "  ";
	}
	



	string pathToSubmit = "./Source/1611985/1";
	Run(pathToSubmit);
	Mark(pathToSubmit);
	//Mark(pathToSubmit);

	cout << endl;
	return 0;
}

