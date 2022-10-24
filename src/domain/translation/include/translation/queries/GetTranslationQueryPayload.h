#pragma once

#include <map>
#include <optional>
#include <string>

#include "Language.h"
#include "collection/StlOperators.h"

namespace glossary::translation
{
struct GetTranslationQueryPayload
{
    std::string text;
    Language sourceLanguage;
    Language targetLanguage;
};

inline bool operator==(const GetTranslationQueryPayload& lhs, const GetTranslationQueryPayload& rhs)
{
    return (lhs.text == rhs.text && lhs.sourceLanguage == rhs.sourceLanguage &&
            lhs.targetLanguage == rhs.targetLanguage);
}

inline std::ostream& operator<<(std::ostream& os,
                                const GetTranslationQueryPayload& getTranslationQueryPayload)
{
    return os << "{text:" << getTranslationQueryPayload.text
              << ",sourceLanguage:" << getTranslationQueryPayload.sourceLanguage
              << ",targetLanguage:" << getTranslationQueryPayload.targetLanguage << "}";
}
}
