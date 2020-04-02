#pragma once

#include <map>
#include <ostream>
#include <string>

namespace glossary::translator
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
    std::map<Language, std::string> languageString{{Language::English, "English"},
                                                   {Language::Polish, "Polish"}};
    return os << languageString.at(language);
}

inline std::string toLanguageCode(Language language)
{
    std::map<Language, std::string> languageCodes{{Language::English, "en"}, {Language::Polish, "pl"}};
    return languageCodes.at(language);
}
}
