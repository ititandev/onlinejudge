#include "Unzip.h"
bool Unzip(const string& filename, const string& directory)
    {
    CkZip zip;
    bool success;

    success = zip.UnlockComponent("Anything for 30-day trial");
    if (success != true) return false;

    success = zip.OpenZip(filename.c_str());
    if (success != true) {
        return false;
    }
    int unzipCount;
    unzipCount = zip.Unzip(directory.c_str());
    if (unzipCount < 0) {
        return false;
    }
    else {
        return true;
    }
    }
