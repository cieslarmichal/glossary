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

inline std::ostream& operator<<(std::ostream& os, const Translation& translation)
{
    os << translation.sourceText << "-" << translation.translatedText;
    return os;
}
}
