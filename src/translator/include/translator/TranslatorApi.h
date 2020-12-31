#pragma once

#ifdef _WIN32
#    define TRANSLATOR_API __declspec(dllexport)
#elif
#    define TRANSLATOR_API
#endif