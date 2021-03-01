#pragma once

#ifdef _WIN32
#    define DICTIONARY_SERVICE_API __declspec(dllexport)
#else
#    define DICTIONARY_SERVICE_API
#endif
