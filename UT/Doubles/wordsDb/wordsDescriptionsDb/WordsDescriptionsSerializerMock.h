#pragma once

#include "gmock/gmock.h"

#include "wordsDb/wordsDescriptionsDb/WordsDescriptionsSerializer.h"

namespace wordsDb::wordsDescriptionsDb
{

class WordsDescriptionsSerializerMock : public WordsDescriptionsSerializer
{
public:
    MOCK_CONST_METHOD1(serialize, std::string(const WordsDescriptions&));
    MOCK_CONST_METHOD1(deserialize, WordsDescriptions(const std::string&));
};
}