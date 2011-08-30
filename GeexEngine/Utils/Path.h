#ifndef _GX_PATH_H_
#define _GX_PATH_H_

#include <Common/GeexEngineExports.h>
#include <string>

class GEEXENGINE_API Path
{
public:
    Path(std::string &p);
    Path(const char* p);

    //operators
    Path& operator+= (const Path& other);
    Path operator+ (const Path& other) const { return Path(*this) += other; }

    //other functions
    //Path& Normalize();
    bool Exists();
    bool IsFile();

    static char GetPathSeparator();

private:
    std::string path;
};

#endif
