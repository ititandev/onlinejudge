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

string Run(const string& cmd, bool& success, const string& logfile)
{
    try
  	{
    		string com=cmd+" &>> "+logfile;
    		int succ=system(com.c_str());
    		fstream f(logfile,ios::out|ios::app);
    		string output;
    		string tmp;
    		while(!f.eof())
    		{
        		getline(f,tmp);
      	 		output+=tmp+"\n";
    		} 
    		success=(succ==0);
    		return output;
    	}
    catch(exception& e)
    {

        throw;
    }
}
