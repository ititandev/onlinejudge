#ifndef SourcePrepare_H
#define SourcePrepare_H
#include <queue>
#include <string>
#include "../include/Resource.h"
class SourcePrepare
{
private:
	std::priority_queue<FileInfo> fileList;
	SourcePrepare();
	static SourcePrepare s_instance;
	std::string getFolder(const std::string& path, const std::string& ass_name);
public:
	void Recover();
	void LoadSource();
	FileInfo getSourceInfo();
	bool isSourceEmpty();
	static SourcePrepare& instance();
};
#endif