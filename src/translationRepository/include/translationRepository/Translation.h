#pragma once

#include <ostream>
#include <vector>

#include "SourceText.h"
#include "TranslatedText.h"

namespace glossary::translationRepository
{
struct Translation
{
    SourceText sourceText;
    TranslatedText translatedText;
};

using Translations = std::vector<Translation>;

inline bool operator==(const Translation& lhs, const Translation& rhs)
{
    return (lhs.translatedText == rhs.translatedText && lhs.sourceText == rhs.sourceText);
}

inline std::string toString(const Translation& translation)
{
    return "{sourceText:" + translation.sourceText + ".translatedText:" + translation.translatedText + "}";
}

inline std::ostream& operator<<(std::ostream& os, const Translation& translation)
{
    return os << toString(translation);
}
}
