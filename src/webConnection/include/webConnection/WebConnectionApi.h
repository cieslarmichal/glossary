#pragma once

#ifdef _WIN32
#    define WEB_CONNECTION_API __declspec(dllexport)
#else
#    define WEB_CONNECTION_API
#endif
