#pragma once

#ifdef _WIN32
#    define UTILS_API __declspec(dllexport)
#else
#    define UTILS_API
#endif