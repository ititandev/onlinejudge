#include "../include/MyUtility.h"

#ifndef USE_BOOST
    #include <chrono>
    #include <ratio>
    #include <experimental/filesystem>
    namespace fs= std::experimental::filesystem;
    using namespace std::chrono;
#else
    #include <boost/chrono.hpp>
    #include <boost/ratio.hpp>
    #include <boost/filesystem.hpp>
    namespace fs=boost::filesystem;
    using namespace boost::chrono;
#endif
using namespace zipper;
using namespace std;
long getTimeStamp(const std::string& p)
{
    fs::path Path(p);
    #ifndef USE_BOOST
    auto ftime=duration_cast<milliseconds>(fs::last_write_time(Path).time_since_epoch()).count();
    #else
    std::time_t ftime=fs::last_write_time(Path);
    #endif
    return ftime;   
    
}
bool Unzip(const string& filename, const string& destination)
{
       Unzipper zip(filename);
       bool isSuccess=zip.extract(destination);
       zip.close();
       return isSuccess;
}
