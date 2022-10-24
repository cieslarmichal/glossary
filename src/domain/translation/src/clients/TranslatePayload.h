#pragma once

#include <map>
#include <optional>
#include <string>

#include "Language.h"
#include "collection/StlOperators.h"

namespace glossary::translation
{
struct TranslatePayload
{
    std::string text;
    Language sourceLanguage;
    Language targetLanguage;
};

inline bool operator==(const TranslatePayload& lhs, const TranslatePayload& rhs)
{
    return (lhs.text == rhs.text && lhs.sourceLanguage == rhs.sourceLanguage &&
            lhs.targetLanguage == rhs.targetLanguage);
}

inline std::ostream& operator<<(std::ostream& os, const TranslatePayload& translatePayload)
{
    return os << "{text:" << translatePayload.text << ",sourceLanguage:" << translatePayload.sourceLanguage
              << ",targetLanguage:" << translatePayload.targetLanguage << "}";
}
}
