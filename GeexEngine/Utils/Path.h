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

    bool operator== (const Path& other) const;
    bool operator!= (const Path& other) const { return !(*this == other); }

    //other functions
    //Path& Normalize();
    bool Exists() const;
    bool IsFile() const;

    const char* GetExtension() const;
    const char* GetPath() const;

    static char GetPathSeparator();

private:
    std::string path;
};

#endif
