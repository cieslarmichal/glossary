#pragma once

#include "gmock/gmock.h"

#include "DictionaryWordRandomizer.h"

namespace glossary::dictionary
{
class DictionaryWordRandomizerMock : public DictionaryWordRandomizer
{
public:
    MOCK_CONST_METHOD1(randomize, DictionaryWord(const std::vector<DictionaryWord>&));
};
}