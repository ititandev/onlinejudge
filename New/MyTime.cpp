#include <chrono>
#include <ratio>
#include <experimental/filesystem>
#include "MyTime.h"
namespace fs = std::experimental::filesystem;
using namespace std::chrono;
long getTimeStamp(const std::string& p)
{
    fs::path Path(p);
    auto ftime=fs::last_write_time(Path);
    return duration_cast<std::chrono::milliseconds>(ftime.time_since_epoch()).count();   
    
}
