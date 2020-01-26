#pragma once

#include "gmock/gmock.h"

#include "wordsDb/translationsDb/TranslationsSerializer.h"

namespace wordsDb::translationsDb
{

class TranslationsSerializerMock : public TranslationsSerializer
{
public:
    MOCK_CONST_METHOD1(serialize, std::string(const Translations&));
    MOCK_CONST_METHOD1(deserialize, Translations(const std::string&));
};
}
