#pragma once

#include "gmock/gmock.h"

#include "DictionaryWordsRetriever.h"

namespace glossary::dictionary
{
class DictionaryWordsRetrieverMock : public DictionaryWordsRetriever
{
public:
    MOCK_CONST_METHOD1(retrieveDictionaryWords,
                       std::optional<std::vector<DictionaryWord>>(const std::string&));
    MOCK_CONST_METHOD1(retrieveEnglishWords,
                       std::optional<std::vector<std::string>>(const std::string&));
    MOCK_CONST_METHOD0(retrieveEnglishWords, std::vector<std::string>());
};
}