#pragma once

#ifdef _WIN32
#    define TRANSLATOR_REPOSITORY_API __declspec(dllexport)
#else
#    define TRANSLATOR_REPOSITORY_API
#endif