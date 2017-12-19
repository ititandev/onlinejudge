#include "sort.h"
#include <iostream>
using namespace std;
int main(int argv, char** args)
{
	if(argv!=3)
	{
		cerr<<"Invalid number of arguments!";
		exit(-1);
	}
	fstream in(args[1],ios::in);
	fstream out(args[2],ios::out);
	Input(in);
	sort();
	Output(out);
	return 0;
}
