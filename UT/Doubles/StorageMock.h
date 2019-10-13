#pragma once

#include "gmock/gmock.h"

#include "Storage.h"

class StorageMock : public Storage
{
public:
    MOCK_METHOD1(addWord, void(const Word&));
    MOCK_CONST_METHOD1(getWord, boost::optional<Word>(const EnglishWord&));
    MOCK_CONST_METHOD0(getWords, Words());
    MOCK_CONST_METHOD1(contains, bool(const EnglishWord&));
    MOCK_CONST_METHOD0(size, Words::size_type());
    MOCK_CONST_METHOD0(empty, bool());
    MOCK_CONST_METHOD0(begin, Words::const_iterator());
    MOCK_CONST_METHOD0(end, Words::const_iterator());
};
