#pragma once

#include <string>
#include "UtilsApi.h"

namespace utils
{
UTILS_API std::string getProjectPath(const std::string&);

#ifdef _WIN32
const std::string slash{"\\"};
#else
const std::string slash{"/"};
#endif
}