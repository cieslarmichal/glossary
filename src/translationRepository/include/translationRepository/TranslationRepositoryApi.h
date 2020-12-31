#pragma once

#ifdef _WIN32
#    define TRANSLATOR_REPOSITORY_API __declspec(dllexport)
#elif
#    define TRANSLATOR_REPOSITORY_API
#endif