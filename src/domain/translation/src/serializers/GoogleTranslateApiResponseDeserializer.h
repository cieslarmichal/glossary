#pragma once

#include "GoogleTranslateApiResponse.h"

namespace glossary::translation
{
class GoogleTranslateApiResponseDeserializer
{
public:
    virtual ~GoogleTranslateApiResponseDeserializer() = default;

    virtual GoogleTranslateApiResponse deserialize(const std::string& responseBody) const = 0;
};
}
