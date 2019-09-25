#pragma once

#include "gmock/gmock.h"

#include "Database.h"

class DatabaseMock : public Database
{
    MOCK_CONST_METHOD0(readNextWord, boost::optional<WordWithTranslation>());
    MOCK_CONST_METHOD1(getWordExistenceInfo, boost::optional<WordExistenceInfo>(const EnglishWord&));
    MOCK_CONST_METHOD1(getWordDescription, boost::optional<WordDescription>(const EnglishWord &));
    MOCK_CONST_METHOD1(writeWordExistenceInfo, void(const WordExistenceInfo &));
    MOCK_CONST_METHOD1(writeWordDescription, void(const WordDescription &));
};
