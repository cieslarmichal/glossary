#include "StatisticsMemoryStorage.h"

#include "boost/algorithm/cxx11/any_of.hpp"
#include "gtest/gtest.h"

using namespace ::testing;
using namespace glossary::statistics;
using namespace boost::algorithm;

namespace
{
const std::string englishWord1{"englishWord1"};
const std::string englishWord2{"englishWord2"};
const std::string englishWord3{"englishWord3"};
const WordStatistics wordStats1{englishWord1, 8, 0};
const WordStatistics wordStats2{englishWord2, 8, 0};
const std::vector<WordStatistics> twoWordsStatistics{wordStats1, wordStats2};
const WordStatistics wordStats3{englishWord3, 7, 0};
const WordStatistics wordStats3AfterCorrectAnswer{englishWord3, 8, 0};
const WordStatistics wordStats3AfterIncorrectAnswer{englishWord3, 7, 1};

const std::vector<WordStatistics> statsWithWord3AfterCorrectAnswer{wordStats3AfterCorrectAnswer};
const std::vector<WordStatistics> statsWithWord3AfterIncorrectAnswer{wordStats3AfterIncorrectAnswer};
}

class StatisticsMemoryStorageTest : public Test
{
public:
    StatisticsMemoryStorage storage;
};

TEST_F(StatisticsMemoryStorageTest, givenWordStatsAdditionNotExistingInStorage_shouldAddWordStats)
{
    ASSERT_TRUE(storage.empty());

    storage.addWordStatistics(wordStats1);

    ASSERT_FALSE(storage.empty());
    ASSERT_EQ(storage.size(), 1);
}

TEST_F(StatisticsMemoryStorageTest, givenWordStatsAdditionExistingInStorage_shouldNotAddWordStats)
{
    storage.addWordStatistics(wordStats1);
    storage.addWordStatistics(wordStats1);

    ASSERT_EQ(storage.size(), 1);
}

TEST_F(StatisticsMemoryStorageTest, givenTwoWordStats_shouldReturnStatistics)
{
    storage.addWordStatistics(wordStats1);
    storage.addWordStatistics(wordStats2);

    const auto actualStats = storage.getStatistics();

    ASSERT_EQ(actualStats, twoWordsStatistics);
}

TEST_F(StatisticsMemoryStorageTest, givenExistingInStorageEnglishWord_shouldReturnWordStats)
{
    storage.addWordStatistics(wordStats1);

    const auto wordStatistics = storage.getWordStatistics(englishWord1);

    ASSERT_EQ(wordStatistics, wordStats1);
}

TEST_F(StatisticsMemoryStorageTest, givenNonExistingInStorageEnglishWord_shouldReturnNone)
{
    const auto wordStatistics = storage.getWordStatistics(englishWord1);

    ASSERT_EQ(wordStatistics, std::nullopt);
}

TEST_F(StatisticsMemoryStorageTest, givenExistingInStorageEnglishWord_shouldIncreaseCorrectAnswers)
{
    storage.addWordStatistics(wordStats3);
    storage.addCorrectAnswer(englishWord3);

    const auto actualWordStatistics = storage.getWordStatistics(englishWord3);
    ASSERT_EQ(*actualWordStatistics, wordStats3AfterCorrectAnswer);
}

TEST_F(StatisticsMemoryStorageTest, givenNonExistingInStorageEnglishWord_shouldNotIncreaseCorrectAnswers)
{
    storage.addCorrectAnswer(englishWord3);

    const auto wordStatistics = storage.getStatistics();
    ASSERT_FALSE(any_of(wordStatistics, [&](const WordStatistics& ws) { return ws == wordStats3AfterCorrectAnswer; }));
}

TEST_F(StatisticsMemoryStorageTest, givenExistingInStorageEnglishWord_shouldIncreaseIncorrectAnswers)
{
    storage.addWordStatistics(wordStats3);
    storage.addIncorrectAnswer(englishWord3);

    const auto actualWordStatistics = storage.getWordStatistics(englishWord3);
    ASSERT_EQ(*actualWordStatistics, wordStats3AfterIncorrectAnswer);
}

TEST_F(StatisticsMemoryStorageTest, givenNonExistingInStorageEnglishWord_shouldNotIncreaseIncorrectAnswers)
{
    storage.addIncorrectAnswer(englishWord3);

    const auto wordStatistics = storage.getStatistics();
    ASSERT_FALSE(
        any_of(wordStatistics, [&](const WordStatistics& ws) { return ws == wordStats3AfterIncorrectAnswer; }));
}

TEST_F(StatisticsMemoryStorageTest, shouldResetStatistics)
{
    storage.addWordStatistics(wordStats1);
    storage.addWordStatistics(wordStats2);

    storage.resetStatistics();

    const auto stats = storage.getStatistics();
    ASSERT_FALSE(
        any_of(stats, [&](const WordStatistics& ws) { return (ws.correctAnswers != 0 && ws.incorrectAnswers != 0); }));
}

TEST_F(StatisticsMemoryStorageTest, givenWordAddition_shouldContainThisWord)
{
    storage.addWordStatistics(wordStats1);

    ASSERT_TRUE(storage.contains(wordStats1.englishWord));
}

TEST_F(StatisticsMemoryStorageTest, givenInitStorage_shouldBeEmpty)
{
    ASSERT_TRUE(storage.empty());
}
