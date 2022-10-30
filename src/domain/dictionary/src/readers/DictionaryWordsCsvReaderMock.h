#pragma once

#include "gmock/gmock.h"

#include "DictionaryWordsCsvReader.h"

namespace glossary::dictionary
{
class DictionaryWordsCsvReaderMock : public DictionaryWordsCsvReader
{
public:
    MOCK_METHOD(std::vector<DictionaryWord>, readDictionaryWords, (const std::string& absolutePath), (const));
};
}
