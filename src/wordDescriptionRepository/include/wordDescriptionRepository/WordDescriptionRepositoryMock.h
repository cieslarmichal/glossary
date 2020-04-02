#pragma once

#include "gmock/gmock.h"

#include "WordDescriptionRepository.h"

namespace glossary::wordDescriptionRepository
{
class WordDescriptionRepositoryMock : public WordDescriptionRepository
{
public:
    MOCK_METHOD1(addWordDescription, void(const WordDescription&));
    MOCK_CONST_METHOD1(getWordDescription, boost::optional<WordDescription>(const EnglishWord&));
    MOCK_CONST_METHOD0(getWordsDescriptions, WordsDescriptions());
    MOCK_CONST_METHOD1(contains, bool(const EnglishWord&));
};

}
