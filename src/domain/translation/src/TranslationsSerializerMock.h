#pragma once

#include "gmock/gmock.h"

#include "TranslationsSerializer.h"

namespace glossary::translation
{
class TranslationsSerializerMock : public TranslationsSerializer
{
public:
    MOCK_CONST_METHOD1(serialize, std::string(const std::vector<Translation>&));
    MOCK_CONST_METHOD1(deserialize, std::vector<Translation>(const std::string&));
};
}
