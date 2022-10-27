#pragma once

#include "gmock/gmock.h"

#include "WordsApiClient.h"

namespace glossary::dictionary
{
class WordsApiClientMock : public WordsApiClient
{
public:
    MOCK_METHOD(std::vector<std::string>, getWordDefinitions, (const std::string& englishWord), (const));
    MOCK_METHOD(std::vector<std::string>, getWordExamples, (const std::string& englishWord), (const));
    MOCK_METHOD(std::vector<std::string>, getWordSynonyms, (const std::string& englishWord), (const));
};
}
