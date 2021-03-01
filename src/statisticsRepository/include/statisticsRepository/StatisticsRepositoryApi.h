#pragma once

#ifdef _WIN32
#    define STATISTICS_REPOSITORY_API __declspec(dllexport)
#else
#    define STATISTICS_REPOSITORY_API
#endif