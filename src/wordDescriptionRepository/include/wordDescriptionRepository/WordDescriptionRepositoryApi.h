#pragma once

#ifdef _WIN32
#    define WORD_DESCRIPTION_REPOSITORY_API __declspec(dllexport)
#elif
#    define WORD_DESCRIPTION_REPOSITORY_API
#endif