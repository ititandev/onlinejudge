#include "../include/CRM.h"
#include "../include/MyLog.h"
#include "../include/xmlProcess.h"
#include "../include/FileProcess.h"
#include "../include/ExcuteCmd.h"
#include "../include/MyException.h"
#include "../include/FileCompare.h"
#include <iomanip>
#include "../include/FormatOutput.h"
void CRM::CreateBuildXml()
{
	if (File(fileInfo.getPath() + "/pro.xml").isFileExist())
	{
		string& config = Resource::ass_config(fileInfo.ass_num).xml_yes;
		if (config == "auto")
			createBuildXml(fileInfo.getPath());
		else if (config == "hard")
		{
			if (!File(fileInfo.getPath() + "/pro.xml").deleteFile())
			{
				studentLog.WriteToFile("Error pro.xml");
				SystemLog::instance()->WriteToFile("Error delete " + fileInfo.getPath() + "/pro.xml");
				throw MyException("Error pro.xml");
			}
			File(Resource::ass_config(fileInfo.ass_num).xml_path).copyTo(fileInfo.getPath() + "/pro.xml");
			SystemLog::instance()->WriteToFile("Copy " + Resource::ass_config(fileInfo.ass_num).xml_path + " to " + fileInfo.getPath() + "/pro.xml");
		}
		else if (config == "keep")
			;
		else if (config == "error")
		{
			studentLog.WriteToFile("Error pro.xml");
			throw MyException("Error pro.xml");
		}
		else
		{
			studentLog.WriteToFile("Error pro.xml");
			SystemLog::instance()->WriteToFile("Error config xml_yes = '" + config + "'");
			throw MyException("Error pro.xml");
		}
	}
	else
	{
		string& config = Resource::ass_config(fileInfo.ass_num).xml_no;
		if (config == "auto")
			createBuildXml(fileInfo.getPath());
		else if (config == "hard")
		{
			if (!File(fileInfo.getPath() + "/pro.xml").deleteFile())
			{
				studentLog.WriteToFile("Error pro.xml");
				SystemLog::instance()->WriteToFile("Error delete " + fileInfo.getPath() + "/pro.xml");
				throw MyException("Error pro.xml");
			}
			File(Resource::ass_config(fileInfo.ass_num).xml_path).copyTo(fileInfo.getPath() + "/pro.xml");
			SystemLog::instance()->WriteToFile("Copy " + Resource::ass_config(fileInfo.ass_num).xml_path + " to " + fileInfo.getPath() + "/pro.xml");
		}
		else if (config == "error")
		{
			studentLog.WriteToFile("Error pro.xml");
			throw MyException("Error pro.xml");
		}
		else
		{
			studentLog.WriteToFile("Error pro.xml");
			SystemLog::instance()->WriteToFile("Error config xml_no  = '" + config + "'");
			throw MyException("Error pro.xml");
		}
	}

}

CRM::CRM(const FileInfo& fileinfo):fileInfo(fileinfo),studentLog(fileInfo)
{
}

void CRM::Compile()
{
	try
	{
		SystemLog::instance()->WriteToFile("Compiling " + fileInfo.getPath()+"...");
		studentLog.WriteToFile("Compiling....");
		CreateBuildXml();
		createMakeFile(fileInfo.getPath());
		//string cmd2 = "cd " + fileInfo.getPath() + "; make &>>"+studentLog.getFilePath();
		//string cmd2="make -C "+fileInfo.getPath()+" &>>"+studentLog.getFilePath();
		string cmd="/usr/bin/make";
		vector<string> params;
		params.push_back("--no-print-directory");
		params.push_back("-C");
		params.push_back(fileInfo.getPath());
		int succ=cmdExec(cmd,params,-1,studentLog.getFilePath())==0;
		if (!succ)
		{
			throw MyException("Compile error");
		}
		
	}
	catch(exception& e)
	{
		throw;
	}
	catch(...)
	{
		throw;
	}
}
void CRM::Run()
{
	try
	{
		SystemLog::instance()->WriteToFile("Running " + fileInfo.getPath());
		studentLog.WriteToFile("Runing....");
		string pathToSubmit = fileInfo.getPath();
		//string remove = "rm -f " + pathToSubmit + "/*.out";
		string command="/usr/bin/rm";
		vector<string> params;
		params.push_back("-f");
		params.push_back(pathToSubmit+"/*.out");
		cmdExec(command,params);
		for (size_t i = 0; i < Resource::ass_config(fileInfo.ass_num).testcase_num; i++)
		{
			//string command = "timeout " + Resource::ass_config(fileInfo.ass_num).timeout + " " + pathToSubmit + "/program ";
			string command = pathToSubmit+"/program";
			vector<string> params;
			params.push_back(Resource::ass_config(fileInfo.ass_num).testcase_path + "/" + to_string(i) + ".in");
			params.push_back(pathToSubmit + "/" + to_string(i) + ".out");
//			string getTimeout=string(" ; if [ $? -eq 124 ]; then echo \"Timeout error\";fi") + " &>>"+studentLog.getFilePath() ;
//			cmdExec(command + param+getTimeout);
			//int res=cmdExec(command,param1,param2,stoi(Resource::ass_config(fileInfo.ass_num).timeout)*1000);
			int res=cmdExec(command,params,stoi(Resource::ass_config(fileInfo.ass_num).timeout));
			switch(res)
			{
				case TIMEOUT:
				studentLog.WriteToFile("Timeout error!");
				break;
				case RUNTIME_ERROR:
				studentLog.WriteToFile("Can't run the program !");
				break;
				
			}
		}
	}
	catch (exception& e)
	{
		throw;
	}
	catch(...)
	{
		throw;
	}
}
void CRM::MarkPoint()
{
	try
	{
		SystemLog::instance()->WriteToFile("Marking " + fileInfo.getPath());
		string pathToSubmit = fileInfo.getPath();
		//string remove = "rm -f " + pathToSubmit + "/score.log";
		string command="/usr/bin/rm";
		vector<string> params;
		params.push_back("-f");
		params.push_back(pathToSubmit+"/score.log");
		cmdExec(command,params);
		fstream file(pathToSubmit + "/score.log", ios::out);
		file<<fileInfo.getHumanTime()<<endl;
		int pass_num = 0;
		string ss;
		for (size_t i = 0; i < Resource::ass_config(fileInfo.ass_num).testcase_num; i++)
		{
			ss += "Testcase " + to_string(i + 1) + "\n";
			ifstream origin(Resource::ass_config(fileInfo.ass_num).testcase_path + "/" + to_string(i) + ".out");
			ifstream compare(pathToSubmit + "/" + to_string(i) + ".out");
			bool res;
			if(Resource::ass_config(fileInfo.ass_num).output_format!="-1")
			{
				ifstream format(Resource::ass_config(fileInfo.ass_num).output_format);
				res=CompareFile(origin,compare,format);
			}
			else res=equalFiles(origin,compare);
			if (res)
			{
				ss += "Pass";
				pass_num++;
			}
			else
				ss += "Fail";
			if (i < Resource::ass_config(fileInfo.ass_num).testcase_num - 1)
				ss += "\n";
		}
		file << "Score: " << endl << fixed << setprecision(1) << (float)pass_num / Resource::ass_config(fileInfo.ass_num).testcase_num * 10 << endl;
		file << ss;
		file.close();
	}
	catch (exception& e)
	{
		throw;
	}
	catch(...)
	{
		throw;
	}
}
static void CRM::Execute(const FileInfo& fileInfo)
{
	CRM crm(fileInfo);	
	try
	{

		SystemLog::instance()->WriteToFile("Start auto mark for " + fileInfo.getPath());
		int ass_num = fileInfo.ass_num;
		bool write = false;
		//string logfile = getLogFile(submitPath);
		crm.Compile();
		crm.Run();
		crm.MarkPoint();
		//File(logfile).moveTo(submitPath + "/log.txt");
		SystemLog::instance()->WriteToFile("Finish auto mark for " + fileInfo.getPath());
	}
	catch (exception& e)
	{
		fstream score(fileInfo.getPath() + "/" + "score.log", ios::out);
		score<<fileInfo.getHumanTime()<<endl;
		score << "Score:\n0";
		score.close();
		SystemLog::instance()->WriteToFile("Error in auto mark for "+fileInfo.getPath()+":"+e.what());
		/*string filename = getLogFile(submitPath);
		fstream f(filename, ios::out | ios::app);
		f << e.what();
		f.close();
		File(filename).moveTo(submitPath + "/log.txt");*/
	}
}
