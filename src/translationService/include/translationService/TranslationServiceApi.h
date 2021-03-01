#pragma once

#ifdef _WIN32
#    define TRANSLATOR_SERVICE_API __declspec(dllexport)
#else
#    define TRANSLATOR_SERVICE_API
#endif