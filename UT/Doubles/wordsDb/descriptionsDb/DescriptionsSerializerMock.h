#pragma once

#include "gmock/gmock.h"

#include "wordsDb/descriptionsDb/DescriptionsSerializer.h"

namespace wordsDb::descriptionsDb
{

class DescriptionsSerializerMock : public DescriptionsSerializer
{
public:
    MOCK_CONST_METHOD1(serialize, std::string(const WordsDescriptions&));
    MOCK_CONST_METHOD1(deserialize, WordsDescriptions(const std::string&));
};
}