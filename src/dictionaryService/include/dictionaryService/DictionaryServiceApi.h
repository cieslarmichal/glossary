#pragma once

#ifdef _WIN32
#    define DICTIONARY_SERVICE_API __declspec(dllexport)
#elif
#    define UTILS_API
#endif
