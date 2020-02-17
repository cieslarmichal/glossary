#pragma once

#include "gmock/gmock.h"

#include "WordsDescriptionsDb.h"

namespace wordsDescriptionsDb
{
class WordsDescriptionsDbMock : public WordsDescriptionsDb
{
public:
    MOCK_CONST_METHOD1(addWordDescription, void(const WordDescription&));
    MOCK_CONST_METHOD1(getWordDescription,
                       boost::optional<WordDescription>(const EnglishWord&));
    MOCK_CONST_METHOD0(getWordsDescriptions, WordsDescriptions());
    MOCK_CONST_METHOD1(contains, bool(const EnglishWord&));
};

}
