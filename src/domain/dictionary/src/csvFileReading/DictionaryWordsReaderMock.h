#pragma once

#include "gmock/gmock.h"

#include "DictionaryWordsReader.h"

namespace glossary::dictionary
{
class DictionaryWordsReaderMock : public DictionaryWordsReader
{
public:
    MOCK_METHOD(std::vector<DictionaryWord>, readDictionaryWords, (const std::string& absolutePath), (const));
};
}
