#include "WordsDbImpl.h"

#include "statisticsDb/StatisticsDbMock.h"
#include "translationsDb/TranslationsDbMock.h"
#include "wordsDescriptionsDb/WordsDescriptionsDbMock.h"

#include "gtest/gtest.h"
#include "wordsDescriptionsDb/WordsDescriptionsDbImpl.h"

using namespace translationsDb;
using namespace wordsDescriptionsDb;
using namespace statisticsDb;
using namespace ::testing;

class WordsDbImplTest : public Test
{
public:
    std::unique_ptr<TranslationsDbMock> translationsDbInit =
        std::make_unique<StrictMock<TranslationsDbMock>>();
    TranslationsDbMock* translationsDb = translationsDbInit.get();
    std::unique_ptr<WordsDescriptionsDbMock> wordsDescriptionsDbInit =
        std::make_unique<StrictMock<WordsDescriptionsDbMock>>();
    WordsDescriptionsDbMock* wordsDescriptionsDb =
        wordsDescriptionsDbInit.get();
    std::unique_ptr<StatisticsDbMock> statisticsDbInit =
        std::make_unique<StrictMock<StatisticsDbMock>>();
    StatisticsDbMock* statisticsDb = statisticsDbInit.get();
    WordsDbImpl database{std::move(translationsDbInit),
                         std::move(wordsDescriptionsDbInit),
                         std::move(statisticsDbInit)};

    const PolishWord polishWord{"polishWord"};
    const EnglishWord englishWord{"englishWord"};
    const WordStatistics wordStats{englishWord, 7, 0};
    const Statistics statistics{wordStats};
    const Translation translation{polishWord, englishWord};
    const Translations translations{translation};
    const WordDescription wordDescription{englishWord, "polishWord", {}};
    const WordsDescriptions wordsDescriptions{wordDescription};
};

TEST_F(WordsDbImplTest, addTranslation)
{
    EXPECT_CALL(*translationsDb, addTranslation(translation));

    database.addTranslation(translation);
}

TEST_F(WordsDbImplTest, getTranslation)
{
    EXPECT_CALL(*translationsDb, getTranslation(polishWord))
        .WillOnce(Return(translation));

    const auto actualTranslation = database.getTranslation(polishWord);

    ASSERT_EQ(*actualTranslation, translation);
}

TEST_F(WordsDbImplTest, getTranslations)
{
    EXPECT_CALL(*translationsDb, getTranslations())
        .WillOnce(Return(translations));

    const auto actualTranslations = database.getTranslations();

    ASSERT_EQ(actualTranslations, translations);
}

TEST_F(WordsDbImplTest, addWordDescription)
{
    EXPECT_CALL(*wordsDescriptionsDb, addWordDescription(wordDescription));

    database.addWordDescription(wordDescription);
}

TEST_F(WordsDbImplTest, getWordDescription)
{
    EXPECT_CALL(*wordsDescriptionsDb, getWordDescription(englishWord))
        .WillOnce(Return(wordDescription));

    const auto actualWordDescription = database.getWordDescription(englishWord);

    ASSERT_EQ(*actualWordDescription, wordDescription);
}

TEST_F(WordsDbImplTest, getWordsDescriptions)
{
    EXPECT_CALL(*wordsDescriptionsDb, getWordsDescriptions())
        .WillOnce(Return(wordsDescriptions));

    const auto actualWordsDescriptions = database.getWordsDescriptions();

    ASSERT_EQ(actualWordsDescriptions, wordsDescriptions);
}

TEST_F(WordsDbImplTest, containsWordDescription)
{
    EXPECT_CALL(*wordsDescriptionsDb, contains(englishWord))
        .WillOnce(Return(true));

    const auto containsWordDescription =
        database.containsWordDescription(englishWord);

    ASSERT_TRUE(containsWordDescription);
}

TEST_F(WordsDbImplTest, getWordStatistics)
{
    EXPECT_CALL(*statisticsDb, getWordStatistics(englishWord))
        .WillOnce(Return(wordStats));

    const auto actualWordStatistics = database.getWordStatistics(englishWord);

    ASSERT_EQ(*actualWordStatistics, wordStats);
}

TEST_F(WordsDbImplTest, getStatistics)
{
    EXPECT_CALL(*statisticsDb, getStatistics()).WillOnce(Return(statistics));

    const auto actualWordStatistics = database.getStatistics();

    ASSERT_EQ(actualWordStatistics, statistics);
}

TEST_F(WordsDbImplTest, addWordStatistics)
{
    EXPECT_CALL(*statisticsDb, addWordStatistics(wordStats));

    database.addWordStatistics(wordStats);
}

TEST_F(WordsDbImplTest, addCorrectAnswer)
{
    EXPECT_CALL(*statisticsDb, addCorrectAnswer(englishWord));

    database.addCorrectAnswer(englishWord);
}

TEST_F(WordsDbImplTest, addIncorrectAnswer)
{
    EXPECT_CALL(*statisticsDb, addIncorrectAnswer(englishWord));

    database.addIncorrectAnswer(englishWord);
}

TEST_F(WordsDbImplTest, resetStatistics)
{
    EXPECT_CALL(*statisticsDb, resetStatistics());

    database.resetStatistics();
}
