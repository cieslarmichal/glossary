#include "GetExecutablePath.h"

#include <climits>
#include <unistd.h>

namespace common::fileSystem
{
std::string getExecutablePath()
{
    char result[PATH_MAX];

    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);

    return std::string(result, (count > 0) ? static_cast<unsigned long>(count) : 0);
}

}