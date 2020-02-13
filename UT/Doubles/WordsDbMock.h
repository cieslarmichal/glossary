#pragma once

#include "gmock/gmock.h"

#include "WordsDb.h"

class WordsDbMock : public WordsDb
{
public:
    MOCK_METHOD1(addTranslation, void(translationsDb::Translation));
    MOCK_CONST_METHOD1(
        getTranslation,
        boost::optional<translationsDb::Translation>(const PolishWord&));
    MOCK_CONST_METHOD0(translationsDb::Translations, getTranslations());
    MOCK_CONST_METHOD1(addWordDescription,
                       void(const wordsDescriptionsDb::WordDescription&));
    MOCK_CONST_METHOD1(getWordDescription,
                       boost::optional<wordsDescriptionsDb::WordDescription>(
                           const EnglishWord&));
    MOCK_CONST_METHOD0(getWordsDescriptions, WordsDescriptions());
    MOCK_CONST_METHOD1(containsWordDescription, bool(const EnglishWord&));
    MOCK_CONST_METHOD1(
        getWordStatistics,
        boost::optional<statisticsDb::WordStatistics>(const EnglishWord&));
    MOCK_CONST_METHOD0(getStatistics, statisticsDb::Statistics());
    MOCK_METHOD1(addWordStatistics, void(statisticsDb::WordStatistics));
    MOCK_METHOD1(addCorrectAnswer, void(const EnglishWord&));
    MOCK_METHOD1(addIncorrectAnswer, void(const EnglishWord&));
    MOCK_METHOD0(resetStatistics, void());
};
