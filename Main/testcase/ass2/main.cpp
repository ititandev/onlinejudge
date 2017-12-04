#include <iostream>
#include <fstream>
#include "input.h"
#include <iomanip>
#include <cmath>
using namespace std;

int main(int argv, char** args)
{
	if (argv < 3 || argv >3)
	{
		cerr << "Input files error" << endl;
		return -1;
	}
	fstream inp(args[1], ios::in);
	if (!inp)
	{
		cerr << "Can't open file" << endl;
		return -1;
	}
	fstream out(args[2], ios::out);


	double a, b, c;
	readInput(inp,a,b,c);

	if (a == 0)
	{
		if (b == 0)
			if (c == 0)
				out << 3;
			else
				out << 0;
		else
		{
			out << 1 << endl;
			out << setprecision(5) << fixed << -c / b;
		}
	}
	else
	{
		double delta = b*b - 4 * a*c;
		if (delta < 0)
			out << 0;
		else if (delta == 0)
		{
			out << 1 << endl;
			out << setprecision(5) << fixed << -b / 2 * a;
		}
		else
		{
			out << 2 << endl;
			out << setprecision(5) << fixed << (-b - sqrt(delta)) / (2 * a) << " " << setprecision(5) << fixed << (-b + sqrt(delta)) / (2 * a);
		}
	}

	return 0;
}
