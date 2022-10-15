#pragma once

#include "gmock/gmock.h"

#include "WordDescriptionResponseDeserializer.h"

namespace glossary::dictionary
{
class WordDescriptionResponseDeserializerMock : public WordDescriptionResponseDeserializer
{
public:
    MOCK_CONST_METHOD1(deserializeDefinitions, std::vector<std::string>(const std::string&));
    MOCK_CONST_METHOD1(deserializeExamples, std::vector<std::string>(const std::string&));
    MOCK_CONST_METHOD1(deserializeSynonyms, std::vector<std::string>(const std::string&));
};
}