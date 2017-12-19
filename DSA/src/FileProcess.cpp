#include "../include/FileProcess.h"

using namespace std;
File::File(const string& path)
{
    	this->pathFile = fs::path(path);
}
string File::getFilename()
{
	return pathFile.filename().string();
}
string File::getPath()
{
	return pathFile.string();
}
string File::getFilenameOnly()
{
	return pathFile.stem().string();
}
void File::rename(const string& newname)
{
	fs::rename(pathFile, pathFile.parent_path().string() + "/" + newname);
}
void File::copyTo(const string& des)
{
	fs::copy(pathFile, des);
}
void File::moveTo(const string& des)
{
	fs::rename(pathFile, des);
}
bool File::isFileEmpty()
{
	return fs::file_size(pathFile) == 0;
}
bool File::deleteFile()
{
	return fs::remove(pathFile);
}
string File::getExtension()
{
	return pathFile.extension().string();
}
bool File::isFileExist()
{
	return fs::exists(pathFile);
}
bool File::isDirectory()
{
	return fs::is_directory(pathFile);
}

Directory::Directory(const string& filename) :File{ filename }
{
}
bool Directory::create(const string& Path)
{
	return fs::create_directories(Path);
}
int Directory::directoryCount()
{
	int count = 0;
	if (!fs::exists(pathFile)) return count;
#ifndef USE_BOOST
	for (auto& p : fs::directory_iterator(pathFile))
	{
		if (fs::is_directory(p)) count++;
	}
#else
	for (fs::directory_iterator it(pathFile); it != fs::directory_iterator(); ++it)
	{
		if (fs::is_directory(*it)) count++;
	}
#endif
	return count;
}
string Directory::getParentDirectory()
{
	return pathFile.parent_path().string();
}
vector<string> Directory::getListDirectory()
	{
		vector<string> lst;
		if (fs::is_directory(pathFile))
		{
#ifndef USE_BOOST
		for (auto& p : fs::directory_iterator(pathFile))
		{
			if (fs::is_directory(p)) lst.push_back(p.path().string());
		}
#else
		for (fs::directory_iterator it(pathFile); it != fs::directory_iterator(); ++it)
		{
			if (fs::is_directory(*it)) lst.push_back((*it).path().string());
		}
#endif
	}
	return lst;
}
vector<string> Directory::getListFile()
{
	vector<string> lst;
	if (fs::is_directory(pathFile))
	{
#ifndef USE_BOOST
		for (auto& p : fs::directory_iterator(pathFile))
		{
			if (fs::is_regular_file(p)) lst.push_back(p.path().string());
		}
#else 
		for (fs::directory_iterator it(pathFile); it != fs::directory_iterator(); ++it)
		{
			if (fs::is_regular_file(*it)) lst.push_back((*it).path().string());
		}
#endif
	}
		return lst;
}
vector<string> Directory::getListFileWithExtension(const string& extension)
{
	vector<string> lst;
	if (fs::is_directory(pathFile))
	{
#ifndef USE_BOOST
		for (auto& p : fs::directory_iterator(pathFile))
		{
			if (fs::is_regular_file(p) && p.path().extension().string() == extension) lst.push_back(p.path().string());
		}
#else
		for (fs::directory_iterator it(pathFile); it != fs::directory_iterator(); ++it)
		{
			if (fs::is_regular_file(*it) && (*it).path().extension().string() == extension) lst.push_back((*it).path().string());
        }
#endif
	}
	return lst;
}
