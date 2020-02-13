#pragma once

#include "gmock/gmock.h"

#include "wordsDescriptionsDb/WordsDescriptionsStorage.h"

namespace wordsDescriptionsDb
{

class WordsDescriptionsStorageMock : public WordsDescriptionsStorage
{
public:
    MOCK_METHOD1(addWordDescription, void(const WordDescription&));
    MOCK_CONST_METHOD1(getWordDescription,
                       boost::optional<WordDescription>(const EnglishWord&));
    MOCK_CONST_METHOD0(getWordsDescriptions, WordsDescriptions());
    MOCK_CONST_METHOD1(contains, bool(const EnglishWord&));
    MOCK_CONST_METHOD0(size, WordsDescriptions::size_type());
    MOCK_CONST_METHOD0(empty, bool());
    MOCK_CONST_METHOD0(begin, WordsDescriptions::const_iterator());
    MOCK_CONST_METHOD0(end, WordsDescriptions::const_iterator());
};
}