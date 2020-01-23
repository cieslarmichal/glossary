#pragma once

#include "gmock/gmock.h"

#include "wordsDb/descriptionsDb/DescriptionsDb.h"

namespace wordsDb::descriptionsDb
{
class DescriptionsDbMock : public DescriptionsDb
{
public:
    MOCK_CONST_METHOD1(addWord, void(const WordDescription&));
    MOCK_CONST_METHOD1(getWord,
                       boost::optional<WordDescription>(const EnglishWord&));
    MOCK_CONST_METHOD0(getWords, WordsDescriptions());
    MOCK_CONST_METHOD1(contains, bool(const EnglishWord&));
};

}
