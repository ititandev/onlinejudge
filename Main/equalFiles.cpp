#include <iostream>
#include <fstream>
#include <exception>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include "equalFiles.h"
using namespace std;

bool equalFiles(ifstream& in1, ifstream& in2)
{
	if (!in1 || !in2)
		return false;
	ifstream::pos_type size1, size2;

	size1 = in1.seekg(0, ifstream::end).tellg();
	in1.seekg(0, ifstream::beg);

	size2 = in2.seekg(0, ifstream::end).tellg();
	in2.seekg(0, ifstream::beg);

	if (size1 != size2)
		return false;

	static const size_t BLOCKSIZE = 4096;
	size_t remaining = size1;

	while (remaining)
	{
		char buffer1[BLOCKSIZE], buffer2[BLOCKSIZE];
		size_t size = std::min(BLOCKSIZE, remaining);

		in1.read(buffer1, size);
		in2.read(buffer2, size);

		if (0 != memcmp(buffer1, buffer2, size))
			return false;

		remaining -= size;
	}

	return true;
}