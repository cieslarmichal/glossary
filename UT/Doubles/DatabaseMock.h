#pragma once

#include "gmock/gmock.h"

#include "Database.h"

class DatabaseMock : public Database
{
    MOCK_CONST_METHOD1(getWordDescription, boost::optional<WordDescription>(const EnglishWord &));
    MOCK_CONST_METHOD1(saveWord, void(const EnglishWordWithDescription &));
};
