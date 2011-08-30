#ifndef _GX_FILESTREAM_H_
#define _GX_FILESTREAM_H_

#include <Common/GeexEngineExports.h>

#include <cstdio>
#include <string>

//TODO: Async read/write, seeking, filesize

class GEEXENGINE_API FileStream
{
public:
    //Construction/Destruction
    FileStream();
    FileStream(const std::string& filename, const char* mode);
    ~FileStream();

    //Getter
    inline const char* GetMode() { return this->mode; }

    //Open and close
    void Open(const std::string& filename, const char* mode);
    void Close();

    //File read and write
    void Read(size_t len, void* buffer);
    void Write(size_t len, const void* buffer);

    //Whole file operations
    static void Load(const std::string& filename, bool binary, int bufSize, void* buffer);
    static void Save(const std::string& filename, bool binary, int bufSize, void* buffer);
    static void Append(const std::string& filename, bool binary, int bufSize, void* buffer);

private:
    FILE* file;
    const char* mode;
};

#endif
