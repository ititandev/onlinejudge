#include <boost/filesystem.hpp>
#include <iostream>
using namespace std;
namespace fs=boost::filesystem;
int main()
{ 
	fs::path p("test.cpp");
	cout<<fs::last_write_time(p)<<endl;
}
//
