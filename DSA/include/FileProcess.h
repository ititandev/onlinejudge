/*
*Chua cac ham xu ly file va thu muc nhu: tao, xoa, di chuyen, sao chep,...
*Yeu cau bien dich:
*         Neu he thong ho tro C++11: cai dat thu vien boost va bien dich voi chi thi -DUSE_BOOST
*         Neu he thong ho tro C++14: bien dich binh thuong, khong can chi thi -DUSE_BOOST
*Linking:
*         boost: tham so khi linking: -lboost_system -lboost_filesystem
*		  C++14: -lstdc++fs	` 
*/
#ifndef FileProcess_H
#define FileProcess_H
#include <string>
#include <vector>
#ifndef USE_BOOST
	#include <experimental/filesystem>
	namespace fs = std::experimental::filesystem;
#else
	#include <boost/filesystem.hpp>
	namespace fs = boost::filesystem;
#endif
//Lop xy ly cac tac vu he thong lien quan toi file
class File
{
protected:
	fs::path pathFile;
public:
//Khoi tao doi tuong de tham chieu toi 1 file voi duong dan @path
	File(const std::string& path);
//Tra ve file name cua 1 file, bo qua duong dan
	std::string getFilename();
//Tra ve duong dan tuyet doi cua 1 file
	std::string getPath();
//Tra ve file name cua 1 file, bo qua duong dan va phan mo rong
	std::string getFilenameOnly();
//Thay doi ten 1 file thanh @newname
	void rename(const std::string& newname);
//Sao chep 1 file toi @des
//Neu @des la thu muc thi sao chep file vao thu muc do va giu nguyen ten file
//Neu @des la file thi sao chep file vao duong dan va doi ten theo @des
	void copyTo(const std::string& des);
//Di chuyen 1 file toi @des
//Neu @des la thu muc thi di chuyen vao ben trong thu muc
//Neu @des la 1 file thi di chuyen va doi ten theo @des
	void moveTo(const std::string& des);
//Kiem tra 1 file rong hay khong
	bool isFileEmpty();
//Xoa 1 file
	bool deleteFile();
//Tra ve phan mo rong cua 1 file voi format: ".extension"
	std::string getExtension();
//Kiem tra file co ton tai
	bool isFileExist();
//Kiem tra file co la thu muc
	bool isDirectory();
};
class Directory : public File
{
public:
//Tao ra 1 doi tuong tham chieu toi thu muc @filename
	Directory(const std::string& filename);
//Tao ra 1 thu muc moi @Path
//Tra ve true neu tao thu muc moi
//Tra ve false neu thuc muc da ton tai
	static bool create(const std::string& Path);
//Dem so thu muc con cua mot thu muc, khong dem de quy
	int directoryCount();
//Tra ve duong dan thu muc cha cua 1 thu muc
	std::string getParentDirectory();
//Lay danh sach thu muc con cua 1 thu muc
	std::vector<std::string> getListDirectory();
//Lay danh sach file trong 1 thu muc
	std::vector<std::string> getListFile();
//Loc ra danh sach file trong 1 thu muc theo dinh dang @extension, @extension co format: ".extension"
	std::vector<std::string> getListFileWithExtension(const std::string& extension);
};
#endif
