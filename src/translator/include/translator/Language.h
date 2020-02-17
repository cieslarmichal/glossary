#pragma once

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
