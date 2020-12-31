#pragma once

#ifdef _WIN32
#    define TRANSLATOR_SERVICE_API __declspec(dllexport)
#elif
#    define TRANSLATOR_SERVICE_API
#endif