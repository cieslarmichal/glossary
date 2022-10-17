#pragma once

#include <ostream>
#include <vector>

namespace glossary::translation
{
struct Translation
{
    std::string sourceText;
    std::string translatedText;
};

inline bool operator==(const Translation& lhs, const Translation& rhs)
{
    return (lhs.translatedText == rhs.translatedText && lhs.sourceText == rhs.sourceText);
}

inline std::string toString(const Translation& translation)
{
    return "{sourceText:" + translation.sourceText + ",translatedText:" + translation.translatedText + "}";
}

inline std::ostream& operator<<(std::ostream& os, const Translation& translation)
{
    return os << toString(translation);
}
}
