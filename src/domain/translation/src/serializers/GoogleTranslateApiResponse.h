#pragma once

#include <ostream>
#include <vector>

#include "collection/StlOperators.h"
#include "fmt/core.h"

namespace glossary::translation
{
struct GoogleTranslateApiResponseDataTranslation
{
    std::string translatedText;
    std::string detectedSourceLanguage;
};

struct GoogleTranslateApiResponseData
{
    std::vector<GoogleTranslateApiResponseDataTranslation> translations;
};

struct GoogleTranslateApiResponse
{
    GoogleTranslateApiResponseData data;
};

inline bool operator==(const GoogleTranslateApiResponseDataTranslation& lhs,
                       const GoogleTranslateApiResponseDataTranslation& rhs)
{
    return (lhs.translatedText == rhs.translatedText &&
            lhs.detectedSourceLanguage == rhs.detectedSourceLanguage);
}

inline bool operator==(const GoogleTranslateApiResponseData& lhs, const GoogleTranslateApiResponseData& rhs)
{
    return (lhs.translations == rhs.translations);
}

inline bool operator==(const GoogleTranslateApiResponse& lhs, const GoogleTranslateApiResponse& rhs)
{
    return (lhs.data == rhs.data);
}

inline std::ostream&
operator<<(std::ostream& os,
           const GoogleTranslateApiResponseDataTranslation& googleTranslateApiResponseDataTranslation)
{
    return os << "{"
              << fmt::format("translatedText:{}, detectedSourceLanguage: {}",
                             googleTranslateApiResponseDataTranslation.translatedText,
                             googleTranslateApiResponseDataTranslation.detectedSourceLanguage)
              << "}";
}

inline std::ostream& operator<<(std::ostream& os,
                                const GoogleTranslateApiResponseData& googleTranslateApiResponseData)
{
    return os << googleTranslateApiResponseData.translations;
}

inline std::ostream& operator<<(std::ostream& os,
                                const GoogleTranslateApiResponse& googleTranslateApiResponse)
{
    return os << googleTranslateApiResponse.data;
}
}
