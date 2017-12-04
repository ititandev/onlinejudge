#include <fstream>
#include <sstream>
#include "input.h"
using namespace std;

bool readInput(fstream& inp, double& a, double& b, double& c)
{
	string s;
	getline(inp, s);
	stringstream ss(s);
	ss >> a >> b >> c;
}
