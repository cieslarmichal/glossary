#pragma once
#include "gmock/gmock.h"

#include "WordsMerger.h"

namespace glossary
{
class WordsMergerMock : public WordsMerger
{
public:
    MOCK_CONST_METHOD2(mergeWords, UniqueWords(const dictionaryRepository::DictionaryWords&,
                                               const wordsDescriptionsDb::WordsDescriptions&));
};
}