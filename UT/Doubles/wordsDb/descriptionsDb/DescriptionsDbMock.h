#pragma once

#include "gmock/gmock.h"

#include "wordsDb/descriptionsDb/DescriptionsDb.h"

namespace wordsDb::descriptionsDb
{
class DescriptionsDbMock : public DescriptionsDb
{
public:
    MOCK_CONST_METHOD1(addWord, void(const Word&));
    MOCK_CONST_METHOD1(getWord, boost::optional<Word>(const EnglishWord&));
    MOCK_CONST_METHOD1(contains, bool(const EnglishWord&));
};

}
