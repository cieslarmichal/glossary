#pragma once

#include <map>
#include <ostream>
#include <string>

namespace glossary::translation
{
enum class Language
{
    Polish,
    English
};

inline std::string toString(Language language)
{
    std::map<Language, std::string> languageString{{Language::Polish, "Polish"}, {Language::English, "English"}};

    return languageString.at(language);
}

inline std::ostream& operator<<(std::ostream& os, Language language)
{
    return os << "Language::" << toString(language);
}

inline std::string toLanguageCode(Language language)
{
    std::map<Language, std::string> languageCodes{{Language::English, "en"}, {Language::Polish, "pl"}};

    return languageCodes.at(language);
}
}
