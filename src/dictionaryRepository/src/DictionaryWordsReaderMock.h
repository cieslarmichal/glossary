#pragma once

#include "gmock/gmock.h"

#include "DictionaryWordsReader.h"

namespace dictionaryRepository
{
class DictionaryWordsReaderMock : public DictionaryWordsReader
{
public:
    MOCK_CONST_METHOD1(readDictionaryWords, DictionaryWords(const std::string& absolutePath));
};
}