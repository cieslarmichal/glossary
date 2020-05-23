#pragma once

#include "gmock/gmock.h"

#include "WordDescriptionResponseDeserializer.h"

namespace glossary::wordDescriptionDownloader
{
class WordDescriptionResponseDeserializerMock : public WordDescriptionResponseDeserializer
{
public:
    MOCK_CONST_METHOD1(deserializeDefinitions, wordDescriptionRepository::Definitions(const std::string&));
    MOCK_CONST_METHOD1(deserializeExamples, wordDescriptionRepository::Examples(const std::string&));
    MOCK_CONST_METHOD1(deserializeSynonyms, wordDescriptionRepository::Synonyms(const std::string&));
};
}