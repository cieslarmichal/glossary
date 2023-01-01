#pragma once

#include <ostream>
#include <vector>

#include "fmt/core.h"

#include "collection/StlOperators.h"

namespace glossary::translation
{
struct GoogleTranslateApiResponseDataTranslation
{
    std::string translatedText;
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
    return lhs.translatedText == rhs.translatedText;
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
operator<<(std::ostream& os, const GoogleTranslateApiResponseDataTranslation& googleTranslateApiResponseDataTranslation)
{
    return os << "{" << fmt::format("translatedText:{}", googleTranslateApiResponseDataTranslation.translatedText)
              << "}";
}

inline std::ostream& operator<<(std::ostream& os, const GoogleTranslateApiResponseData& googleTranslateApiResponseData)
{
    return os << googleTranslateApiResponseData.translations;
}

inline std::ostream& operator<<(std::ostream& os, const GoogleTranslateApiResponse& googleTranslateApiResponse)
{
    return os << googleTranslateApiResponse.data;
}
}
