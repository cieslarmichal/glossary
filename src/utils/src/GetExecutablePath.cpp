#include "ProjectAbsolutePath.h"

#include "exceptions/FileNotFound.h"

#ifdef _WIN32
#include <windows.h> //GetModuleFileNameW
#else
#include <limits.h>
#include <unistd.h> //readlink
#endif

namespace utils
{

namespace
{
const std::string projectName{"glossary/"};
const std::string fileNotFoundMessage{"Project directory not found in path: "};
}

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
//    const std::string currentPath = fs::current_path();
//    std::cerr << currentPath;
//    const auto projectNamePosition = currentPath.find(projectName);
//    if (projectNamePosition == std::string::npos)
//    {
//        throw exceptions::FileNotFound{fileNotFoundMessage + currentPath};
//    }
//    return utils::substring(currentPath, 0,
//                            projectNamePosition + projectName.length());
}

}