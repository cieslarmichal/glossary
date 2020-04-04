#pragma once

#include "gmock/gmock.h"

#include "DictionaryWordRandomizer.h"

namespace glossary
{
class DictionaryWordRandomizerMock : public DictionaryWordRandomizer
{
public:
    MOCK_CONST_METHOD1(randomize,
                 dictionaryRepository::DictionaryWord(const dictionaryRepository::DictionaryWords&);
};
}