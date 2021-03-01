#pragma once

#ifdef _WIN32
#    define WORD_DESCRIPTION_DOWNLOADER_API __declspec(dllexport)
#else
#    define WORD_DESCRIPTION_DOWNLOADER_API
#endif