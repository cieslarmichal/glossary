#pragma once

#ifdef _WIN32
#    define GLOSSARY_API __declspec(dllexport)
#else
#    define GLOSSARY_API
#endif