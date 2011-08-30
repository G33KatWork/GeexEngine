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

/*Path& Path::Normalize()
{
    return *this;
}*/

bool Path::Exists()
{
    struct stat st;
    int res = stat(path.c_str(), &st);
    return res == 0;
}

bool Path::IsFile()
{
    struct stat st;
    int res = stat(path.c_str(), &st);
    return (res == 0) && (st.st_mode & S_IFDIR) != S_IFDIR;
}

char Path::GetPathSeparator()
{
#ifdef _WIN32 || _WIN64
    return '\\';
#else
    return '/';
#endif
}
