#ifndef PT_BAC2
#define PT_BAC2


#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>
using namespace std;


void ptbac2(double a, double b, double c)
{
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
}
#endif