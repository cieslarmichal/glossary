#pragma once

#include "../../../../externals/googletest/googlemock/include/gmock/gmock.h"

#include "TranslationService.h"

namespace glossary::translation
{
class TranslationServiceMock : public TranslationService
{
public:
    MOCK_CONST_METHOD4(translate, std::optional<std::string>(const std::string&, Language, Language,
                                                             const std::string& apiKey));
};
}