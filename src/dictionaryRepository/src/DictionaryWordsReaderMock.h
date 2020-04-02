#pragma once

#include "gmock/gmock.h"

#include "DictionaryWordsReader.h"

namespace glossary::dictionaryRepository
{
class DictionaryWordsReaderMock : public DictionaryWordsReader
{
public:
    MOCK_CONST_METHOD1(readDictionaryWords,
                       boost::optional<DictionaryWords>(const std::string& absolutePath));
};
}