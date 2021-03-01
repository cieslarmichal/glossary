#pragma once

#ifdef _WIN32
#    define WORD_DESCRIPTION_SERVICE_API __declspec(dllexport)
#else
#    define WORD_DESCRIPTION_SERVICE_API
#endif