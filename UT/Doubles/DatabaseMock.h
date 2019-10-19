#pragma once

#include "gmock/gmock.h"

#include "Database.h"

class DatabaseMock : public Database
{
public:
    MOCK_CONST_METHOD1(addWord, void(const Word&));
    MOCK_CONST_METHOD1(getWord, boost::optional<Word>(const EnglishWord&));
};
