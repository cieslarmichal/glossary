#pragma once

#include "GoogleTranslateApiResponseDeserializer.h"

namespace glossary::translation
{
class GoogleTranslateApiJsonResponseDeserializer : public GoogleTranslateApiResponseDeserializer
{
public:
    GoogleTranslateApiResponse deserialize(const std::string& responseJsonBody) const override;
};
}
