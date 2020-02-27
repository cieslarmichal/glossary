#include "GetExecutablePath.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <limits.h>
#include <unistd.h>
#endif

namespace utils
{
std::string getExecutablePath()
{
#ifdef _WIN32
    wchar_t path[MAX_PATH] = {0};
    GetModuleFileNameW(NULL, path, MAX_PATH);
    return path;
#else
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    return std::string(result, (count > 0) ? static_cast<unsigned long>(count) : 0);
#endif
}

}