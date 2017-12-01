
#ifdef _STD_C17_
#include <chrono>
#include <ratio>
#include <experimental/filesystem>
namespace fs= experimental::filesystem;
using namespace std::chrono;
#else
#include <boost/chrono.hpp>
#include <boost/ratio.hpp>
#include <boost/filesystem.hpp>
namespace fs=boost::filesystem;
using namespace boost::chrono;
#endif
#include "MyTime.h"

unsigned long getTimeStamp(const std::string& p)
{
    fs::path Path(p);
    std::time_t ftime=fs::last_write_time(Path);
    return ftime;   
    
}
