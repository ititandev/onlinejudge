#include <string>
#include <cstdlib>
#include <ctime>
#include "../include/ExcuteCmd.h"
#include "../include/MyException.h"
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <signal.h>
#include <vector>

using namespace std;

int cmdExec(const string& cmd, vector<string>& param, int timeout, const string& fileOut)
{
	pid_t pid=fork();
	int status;
	clock_t start=clock();
	if(pid<0)
	throw MyException("fork process error");
	else if(pid>0)
	{
		if(timeout==-1) waitpid(pid,&status,0);
		else
		{
			int waittime=0;
			int wpid=0;
			do
			{		
				wpid=waitpid(pid,&status,WNOHANG);
				if(wpid==0)
				{
					if(waittime>timeout)
					{
						kill(pid,SIGTERM);
						return TIMEOUT;
					}
					usleep(100*1000);
					waittime+=100;
				}
			}		
			while(wpid==0);
		}
		return WEXITSTATUS(status);
	}
	else
	{
		char** args=new char*[param.size()+2];
		int i;
		args[0]=(char*)cmd.c_str();
		for(i=0;i<param.size();++i) args[i+1]=(char*)param[i].c_str();
		args[i+1]=NULL;
		int fd=-1;
		if(fileOut!="") fd=open(fileOut.c_str(),O_WRONLY|O_APPEND);
		if(fd!=-1) 
		{
			dup2(fd,1);
			dup2(fd,2);
		}
		execv(cmd.c_str(),args);
		exit(-1); 
	}
}

