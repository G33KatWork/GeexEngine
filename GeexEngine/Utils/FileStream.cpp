#include <Utils/FileStream.h>

#include <Common/GeexEngineException.h>

using namespace std;

FileStream::FileStream()
    : file(NULL),
    mode("")
{}

FileStream::FileStream(const std::string& filename, const char* mode)
    : mode("")
{
    Open(filename, mode);
}

FileStream::~FileStream()
{
    Close();
}

void FileStream::Open(const std::string& filename, const char* mode)
{
    this->mode = mode;
    
    if(!mode || !strcmp(mode, ""))
        throw GeexEngineException("Invalid file stream mode supplied");

    file = fopen(filename.c_str(), mode);

    if(!file)
        throw GeexEngineException("Opening file failed");
}

void FileStream::Close()
{
    if(!file)
        return;

    int r = fclose(file);

    if(r != 0)
        throw GeexEngineException("Closing file failed");

    file = NULL;
}

void FileStream::Read(size_t len, void* buffer)
{
    int r = fread(buffer, len, 1, file);

    if(r != 1)
        if(ferror(file) != 0)
            throw GeexEngineException("Reading from file failed");
}

void FileStream::Write(size_t len, const void* buffer)
{
    int r = fwrite(buffer, len, 1, file);

    if(r != 1)
        throw GeexEngineException("Writing to file failed");
}

void FileStream::Load(const std::string& filename, bool binary, int bufSize, void* buffer)
{
    const char* mode = "r";
    if(binary)
        mode = "rb";

    FileStream stream(filename, mode);
    stream.Read(bufSize, buffer);
    stream.Close();
}

void FileStream::Save(const std::string& filename, bool binary, int bufSize, void* buffer)
{
    const char* mode = "w";
    if(binary)
        mode = "wb";

    FileStream stream(filename, mode);
    stream.Write(bufSize, buffer);
    stream.Close();
}

void FileStream::Append(const std::string& filename, bool binary, int bufSize, void* buffer)
{
    const char* mode = "a";
    if(binary)
        mode = "ab";

    FileStream stream(filename, mode);
    stream.Write(bufSize, buffer);
    stream.Close();
}
