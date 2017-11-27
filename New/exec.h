#ifndef _EXEC_H
#define _EXEC_H
#include <string>
std::string Run(const std::string& cmd, bool& success, const std::string& logfile);
#endif
