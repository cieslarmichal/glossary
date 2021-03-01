#pragma once

#ifdef _WIN32
#    define TRANSLATOR_API __declspec(dllexport)
#else
#    define TRANSLATOR_API
#endif