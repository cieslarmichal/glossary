#pragma once

#include "gmock/gmock.h"

#include "GetSupportedLanguagesQuery.h"

namespace glossary::translation
{
class GetSupportedLanguagesQueryMock : public GetSupportedLanguagesQuery
{
public:
    MOCK_METHOD(std::vector<Language>, getSupportedLanguages, (std::string textToTranslate), (const));
};
}
