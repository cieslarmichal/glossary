#pragma once

#include <string>

namespace translation
{

enum class Language
{
    Polish,
    English
};

inline std::string toLanguageCode(Language language)
{
    if (language == Language::Polish)
    {
        return "pl";
    }
    else if (language == Language::English)
    {
        return "en";
    }
    return {};
}
}
