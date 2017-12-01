#ifdef _STD_C14_
#include <experimental/filesytem>
namespace fs=experimental::filesystem;
#else
#include <boost/filesystem.hpp>
namespace fs=boost::filesystem;
#endif
#include <string>
#include <vector>
using namespace std;


class File
{
	protected:
		fs::path pathFile;
	public:
	File(const string& path)
	{
		this->pathFile = fs::path(path);
	}
	string getFilename() 
	{
		return pathFile.filename().string();
	}
	string getPath()
	{
		return pathFile.string();
	}
	string getFilenameOnly()
	{
		return pathFile.stem().string();
	}
	void rename(const string& newname) 
	{
		fs::rename(pathFile, pathFile.parent_path().string() +"/" +newname);
	}
	void copyTo(const string& des) 
	{
		fs::copy(pathFile, des);
	}
	void moveTo(const string& des) 
	{
		fs::rename(pathFile, des);
	}
	bool isFileEmpty()
	{
		return fs::file_size(pathFile)==0;
	}
	bool deleteFile()
	{
		return fs::remove(pathFile);
	}
	string getExtension()
	{
		return pathFile.extension().string();
	}
	bool isFileExist() 
	{
		return fs::exists(pathFile);
	}
	bool isDirectory() 
	{
		return fs::is_directory(pathFile);
	}
};
class Directory: public File
{
public:
	Directory(const string& filename):File{filename}
	{
	}
	static bool create(const string& Path)
	{
		return fs::create_directories(Path);
	}
	int dirsCount()
	{
		int count=0;
		if(!fs::exists(pathFile)) return count;
#ifdef _STD_C14_
		for(auto& p:fs::directory_iterator(pathFile))
		{
			if(fs::is_directory(p)) count++;
		}
#else
		for(fs::directory_iterator it(pathFile);it!=fs::directory_iterator();++it)
		{
			if(fs::is_directory(*it)) count++;
		}
#endif
		return count;
	}
	string getParentDirectory()
	{
		return pathFile.parent_path().string();
	}
	vector<string> getListDirectory()
	{
		vector<string> lst;
		if(fs::is_directory(pathFile))
		{
#ifdef _STD_C14_
			for(auto& p:fs::directory_iterator(pathFile))
			{
				if(fs::is_directory(p)) lst.push_back(p.path().string());
			}
#else
			for(fs::directory_iterator it(pathFile);it!=fs::directory_iterator();++it)
			{
				if(fs::is_directory(*it)) lst.push_back((*it).path().string());
			}
#endif
		}
		return lst;
	}
	vector<string> getListFile()
	{
		vector<string> lst;
		if(fs::is_directory(pathFile))
		{
#ifdef _STD_C14_
			for(auto& p:fs::directory_iterator(pathFile))
			{
				if(fs::is_regular_file(p)) lst.push_back(p.path().string());
			}
#else 
			for(fs::directory_iterator it(pathFile);it!=fs::directory_iterator();++it)
			{
				if(fs::is_regular_file(*it)) lst.push_back((*it).path().string());
			}
#endif
		}
		return lst;
	}
	vector<string> getListFileWithExtension(const string& extension)
	{
		vector<string> lst;
		if(fs::is_directory(pathFile))
		{
#ifdef _STD_C14_
			for(auto& p:fs::directory_iterator(pathFile))
			{
				if(fs::is_regular_file(p)&&p.path().extension().string()==extension) lst.push_back(p.path().string());
			}
#else
			for(fs::directory_iterator it(pathFile);it!=fs::directory_iterator();++it)
			{
				if(fs::is_regular_file(*it)&&(*it).path().extension().string()==extension) lst.push_back((*it).path().string());
#endif
			}
		}
		return lst;
	}
};
