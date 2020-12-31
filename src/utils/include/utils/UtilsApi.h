#pragma once

#ifdef _WIN32
#    define UTILS_API __declspec(dllexport)
#elif
#    define UTILS_API
#endif

//#ifdef _WIN32
//#    ifdef LIBRARY_EXPORTS
//#        define UTILS_API __declspec(dllexport)
//#    else
//#        define UTILS_API __declspec(dllimport)
//#    endif
//#elif
//#    define UTILS_API
//#endif