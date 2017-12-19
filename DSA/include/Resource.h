#ifndef Resource_H
#define Resource_H
#include <string>
#include <queue>
#include <map>
#include <list>
#include <ctime>
#include "../include/FileProcess.h"


struct ass_config_t
{
	std::string timeout;
	int testcase_num;
	std::string testcase_path;
	std::string xml_yes;
	std::string xml_no;
	std::string xml_path;
	std::string output_format;
};
struct FileInfo
{
	std::string path;
	long timeStamp;
	int ass_num;
	std::string getPath() const
	{
		return path;
	}
	std::string getHumanTime() const
	{
		time_t now=timeStamp;
		struct tm  tstruct;
		char       buf[80];
		tstruct = *localtime(&now);
		strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
		return std::string(buf);
	}
};
bool operator<(const FileInfo& lhs,const FileInfo& rhs);
//Class ho tro viec lay cac thong tin cau hinh cua chuong trinh
class Resource
{
public:
	static int& frame();
	static std::string& lock_path();
	static std::string& source_path();
	static std::string& upload_path();
	static std::string& config_path();
	static int& ass_num();
	static std::string& ass_name(int i);
	static ass_config_t& ass_config(int i);
private:
	/*
   Config

   Parse structured config files

   Config files contains lines with name-value assignements in the form "<name> = <value>".
   Trailing and leading whitespace is stripped. Parsed config entries are stored in
   a symbol map.
   
   Lines beginning with '#' are a comment and ignored.

   Config files may be structured (to arbitrary depth). To start a new config sub group
   (or sub section) use a line in the form of "<name> = (".
   Subsequent entries are stured in the sub group, until a line containing ")" is found.

   Values may reuse already defined names as a variable which gets expanded during
   the parsing process. Names for expansion are searched from the current sub group
   upwards. Finally the process environment is searched, so also environment
   variables may be used as expansion symbols in the config file.

   Errors and warnings are handled by emitting logging messages (see log.h/log.cpp)
   or by calling exit() for severe errors. Depending on project needs this may be replaced
   by exeptions, error return codes, ...
 */

	class Config {
	public:
		/* Parse config file 'configFile'. If the process environment
		 * is provided, environment variables can be used as expansion symbols.
		 */
		Config(std::string configFile);

		~Config();
		
		// get string config entry
		std::string pString(std::string name);

		/* get boolean config entry
		 * A value of Yes/yes/YES/true/True/TRUE leads to true,
		 * all other values leads to false.
		 */
		bool pBool(std::string name);

		// get double config entry; value is parsed using atof()
		double pDouble(std::string name);

		// get int config entry; value is parsed using atoi()
		int pInt(std::string name);

		// get the symbol map (e.g. for iterating over all symbols)
		inline std::map<std::string, std::string>& getSymbols() {
			return symbols;
		}

		// get config sub group
		inline Config* group(std::string name) {
			return groups[name];
		}

		// get config sub group map (e.g. for iterating over all groups)
		inline std::map<std::string, Config*>& getGroups() {
			return groups;
		}

	private:
		// private constructor for sub groups
		Config(std::string name, std::string parentDebugInfo);

		// helper functions for parsing
		void add(std::string name, std::string value);
		void split(std::string in, std::string& left, std::string& right, char c);
		void trim(std::string& s);
		void symbolExpand(std::string& s);
		void symbolExpand(std::map<std::string, std::string>& symbols, std::string& s);
		void envSymbolExpand(std::string& s);
		
		// config group symbol map
		std::map<std::string, std::string> symbols;

		// environment symbol map
		std::map<std::string, std::string> envSymbols;

		// config sub group map
		std::map<std::string, Config*> groups;

		// stack of config groups for parsing (only used in top config element)
		std::list<Config*> groupStack;

		// debug info used for logging messages
		std::string debugInfo;
	};
	class Data
	{
	public:
		int frame;
		std::string lock_path;
		std::string source_path;
		std::string upload_path;
		std::string config_path;
		int ass_num;
		std::string *ass_name;
		ass_config_t *ass_config;
		Data();
		~Data();
	};
	static Data data;

};


#endif
