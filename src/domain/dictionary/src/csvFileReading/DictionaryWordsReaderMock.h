#pragma once

#include "gmock/gmock.h"

#include "DictionaryWordsReader.h"

namespace glossary::dictionary::csvFileReading
{
class DictionaryWordsReaderMock : public DictionaryWordsReader
{
public:
    MOCK_CONST_METHOD1(readDictionaryWords,
                       std::optional<std::vector<DictionaryWord>>(const std::string& absolutePath));
};
}