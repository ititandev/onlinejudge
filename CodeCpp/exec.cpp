#include "File.h"
#include "exec.h"
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <fstream>
#include <string>
#include <array>
using namespace std;

void Run(const string& cmd, bool& success, const string& logfile)
{
    try
  	{
    		string com=cmd+" &>> "+logfile;
    		int succ=system(com.c_str());
    		success=(succ==0);
    }
    catch(exception& e)
    {
        throw;
    }
}
