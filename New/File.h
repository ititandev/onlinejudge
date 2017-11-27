#include <experimental/filesystem>
#include <string>
#include <vector>
using namespace std;
namespace fs = std::experimental::filesystem;

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
		for(auto& p:fs::directory_iterator(pathFile))
		{
			if(fs::is_directory(p)) count++;
		}
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
			for(auto& p:fs::directory_iterator(pathFile))
			{
				if(fs::is_directory(p)) lst.push_back(p.path().string());
			}
		}
		return lst;
	}
	vector<string> getListFile()
	{
		vector<string> lst;
		if(fs::is_directory(pathFile))
		{
			for(auto& p:fs::directory_iterator(pathFile))
			{
				if(fs::is_regular_file(p)) lst.push_back(p.path().string());
			}
		}
		return lst;
	}
	vector<string> getListFileWithExtension(const string& extension)
	{
		vector<string> lst;
		if(fs::is_directory(pathFile))
		{
			for(auto& p:fs::directory_iterator(pathFile))
			{
				if(fs::is_regular_file(p)&&p.path().extension().string()==extension) lst.push_back(p.path().string());
			}
		}
		return lst;
	}
};
