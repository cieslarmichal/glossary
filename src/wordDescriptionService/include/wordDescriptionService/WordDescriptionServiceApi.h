#pragma once

#ifdef _WIN32
#    define WORD_DESCRIPTION_SERVICE_API __declspec(dllexport)
#elif
#    define WORD_DESCRIPTION_SERVICE_API
#endif