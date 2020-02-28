#pragma once

#include <ostream>
#include <vector>

#include "SourceText.h"
#include "TranslatedText.h"

namespace translationsDb
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
    os << translation.translatedText << " " << translation.translatedText;
    return os;
}
}
