#pragma once

#ifdef _WIN32
#    define WEB_CONNECTION_API __declspec(dllexport)
#elif
#    define UTILS_API
#endif
