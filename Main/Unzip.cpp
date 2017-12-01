#include "Unzip.h"
using namespace zipper;
//Unzip "filename" to "directory"
bool Unzip(const string& filename, const string& destination)
{
       Unzipper zip(filename);
       bool isSuccess=zip.extract(destination);
       zip.close();
       return isSuccess;
}

