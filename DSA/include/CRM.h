#ifndef CRM_H
#define CRM_H
#include "../include/MyLog.h"
class CRM
{
private:
	FileInfo fileInfo;
	StudentLog studentLog;
	CRM(const FileInfo& fileInfo);
	void Compile();
	void Run();
	void MarkPoint();
	void CreateBuildXml();
public:
	static void Execute(const FileInfo& fileInfo);
};
#endif