#pragma once

#include <ostream>
#include <string>

namespace translator
{
enum class Language
{
    Polish,
    English
};

using SourceLanguage = Language;
using TargetLanguage = Language;

inline std::ostream& operator<<(std::ostream& os, const Language& language)
{
    if (language == Language::Polish)
    {
        os << "Polish";
    }
    else if (language == Language::English)
    {
        os << "English";
    }
    return os;
}

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
