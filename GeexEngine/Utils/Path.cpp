#include <Utils/Path.h>
#include <sys/stat.h>

//TODO: Much room for improvements here: Normalize(), Filename(), Extension(), IsRelative(), IsAbsolute(), GetRelative(), GetAbsolute(), Iterator for directory traversal etc.

Path::Path(std::string &p)
    : path(p)
{}

Path::Path(const char* p)
    : path(p)
{}

Path& Path::operator+= (const Path& other)
{
    if(path[path.length()-1] != Path::GetPathSeparator())
        path += Path::GetPathSeparator();

    path.append(other.path);
    return *this;
}

bool Path::operator== (const Path& other) const
{
    //FIXME: Normalize bother path before comparison
    return (this->path.compare(other.path) == 0);
}

/*Path& Path::Normalize()
{
    return *this;
}*/

bool Path::Exists() const
{
    struct stat st;
    int res = stat(path.c_str(), &st);
    return res == 0;
}

bool Path::IsFile() const
{
    struct stat st;
    int res = stat(path.c_str(), &st);
    return (res == 0) && (st.st_mode & S_IFDIR) != S_IFDIR;
}

const char* Path::GetExtension() const
{
    if(!IsFile())
        return "";

    size_t dotIndex = path.find_last_of('.');
    if(dotIndex == std::string::npos)
        return "";

    return &path.c_str()[dotIndex+1];
}

const char* Path::GetPath() const
{
    return path.c_str();
}

char Path::GetPathSeparator()
{
#if defined(_WIN32) || defined(_WIN64)
    return '\\';
#else
    return '/';
#endif
}
