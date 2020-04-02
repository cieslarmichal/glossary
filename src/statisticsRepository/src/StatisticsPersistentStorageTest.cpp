#include "StatisticsPersistentStorage.h"

#include "gtest/gtest.h"

#include "StatisticsSerializerMock.h"
#include "utils/FileAccessMock.h"

#include "utils/GetProjectPath.h"
#include "utils/exceptions/FileNotFound.h"

using namespace ::testing;
using namespace glossary::statisticsRepository;

namespace
{
const std::string filepath{utils::getProjectPath("glossary") + "database/statistics.txt"};
const EnglishWord englishWord1{"englishWord1"};
const EnglishWord englishWord2{"englishWord2"};
const EnglishWord englishWord3{"englishWord3"};
const EnglishWord nonExistingWord{"nonExistingWord"};
const WordStatistics wordStats1{englishWord1, 7, 0};
const WordStatistics wordStats2{englishWord2, 8, 0};
const Statistics twoWordsStatistics{wordStats1, wordStats2};
const WordStatistics wordStats1Reset{englishWord1, 0, 0};
const WordStatistics wordStats2Reset{englishWord2, 0, 0};
const Statistics twoResetWordsStatistics{wordStats1Reset, wordStats2Reset};
const WordStatistics wordStats1AfterCorrectAnswer{englishWord1, 8, 0};
const WordStatistics wordStats1AfterIncorrectAnswer{englishWord1, 7, 1};
const Statistics oneWordStatistics{wordStats1};
const Statistics oneWordStatisticsAfterCorrectAnswer{wordStats1AfterCorrectAnswer};
const Statistics oneWordStatisticsAfterIncorrectAnswer{wordStats1AfterIncorrectAnswer};
const Statistics noStatistics{};
}

class StatisticsPersistentStorageTest : public Test
{
public:
    void expectNoWordStatisticsLoad()
    {
        EXPECT_CALL(*fileAccess, readContent(filepath)).WillOnce(Return("some content"));
        EXPECT_CALL(*serializer, deserialize("some content")).WillOnce(Return(noStatistics));
    }

    void expectOneWordStatisticsLoad()
    {
        EXPECT_CALL(*fileAccess, readContent(filepath)).WillOnce(Return("some content"));
        EXPECT_CALL(*serializer, deserialize("some content")).WillOnce(Return(oneWordStatistics));
    }

    void expectTwoWordStatisticsLoad()
    {
        EXPECT_CALL(*fileAccess, readContent(filepath)).WillOnce(Return("some content"));
        EXPECT_CALL(*serializer, deserialize("some content")).WillOnce(Return(twoWordsStatistics));
    }

    std::shared_ptr<utils::FileAccessMock> fileAccess = std::make_shared<StrictMock<utils::FileAccessMock>>();
    std::shared_ptr<StatisticsSerializerMock> serializer =
        std::make_shared<StrictMock<StatisticsSerializerMock>>();
};

TEST_F(StatisticsPersistentStorageTest, givenPersistentStorageWithEmptyFile_shouldBeEmpty)
{
    EXPECT_CALL(*fileAccess, readContent(filepath)).WillOnce(Return(""));
    EXPECT_CALL(*serializer, deserialize("")).WillOnce(Return(Statistics{}));
    StatisticsPersistentStorage persistentStorage{fileAccess, serializer};

    ASSERT_TRUE(persistentStorage.empty());
}

TEST_F(StatisticsPersistentStorageTest, givenPersistentStorageWithFileWithStatistics_shouldLoadStats)
{
    expectTwoWordStatisticsLoad();
    StatisticsPersistentStorage persistentStorage{fileAccess, serializer};

    const auto actualStatistics = persistentStorage.getStatistics();

    ASSERT_EQ(actualStatistics, twoWordsStatistics);
}

TEST_F(StatisticsPersistentStorageTest, givenInvalidFile_shouldReturnNoStats)
{
    EXPECT_CALL(*fileAccess, readContent(filepath)).WillOnce(Throw(utils::exceptions::FileNotFound{""}));
    StatisticsPersistentStorage persistentStorage{fileAccess, serializer};

    const auto actualStats = persistentStorage.getStatistics();

    EXPECT_TRUE(actualStats.empty());
}

TEST_F(StatisticsPersistentStorageTest, givenWordStatsAddition_shouldAddWordStatsAndSerialize)
{
    expectNoWordStatisticsLoad();
    StatisticsPersistentStorage persistentStorage{fileAccess, serializer};
    EXPECT_CALL(*fileAccess, write(filepath, "words"));
    EXPECT_CALL(*serializer, serialize(oneWordStatistics)).WillOnce(Return("words"));

    persistentStorage.addWordStatistics(wordStats1);

    ASSERT_TRUE(persistentStorage.contains(wordStats1.getEnglishWord()));
}

TEST_F(StatisticsPersistentStorageTest,
       givenWordStatsAdditionAndNonExistingFile_shouldAddWordStatsAndNotSerialize)
{
    expectNoWordStatisticsLoad();
    StatisticsPersistentStorage persistentStorage{fileAccess, serializer};
    EXPECT_CALL(*fileAccess, write(filepath, "words")).WillOnce(Throw(utils::exceptions::FileNotFound{""}));
    EXPECT_CALL(*serializer, serialize(oneWordStatistics)).WillOnce(Return("words"));

    persistentStorage.addWordStatistics(wordStats1);

    ASSERT_TRUE(persistentStorage.contains(wordStats1.getEnglishWord()));
}

TEST_F(StatisticsPersistentStorageTest, givenTwoSameWordsStats_shouldAddAndSerializeOnlyOne)
{
    expectNoWordStatisticsLoad();
    StatisticsPersistentStorage persistentStorage{fileAccess, serializer};

    EXPECT_CALL(*fileAccess, write(filepath, "words"));
    EXPECT_CALL(*serializer, serialize(oneWordStatistics)).WillOnce(Return("words"));

    persistentStorage.addWordStatistics(wordStats1);
    persistentStorage.addWordStatistics(wordStats1);

    ASSERT_EQ(persistentStorage.size(), 1);
}

TEST_F(StatisticsPersistentStorageTest, addTwoDifferentWordsStats_shouldAddAndSerializeBoth)
{
    expectNoWordStatisticsLoad();
    StatisticsPersistentStorage persistentStorage{fileAccess, serializer};

    EXPECT_CALL(*fileAccess, write(filepath, "words"));
    EXPECT_CALL(*serializer, serialize(oneWordStatistics)).WillOnce(Return("words"));

    persistentStorage.addWordStatistics(wordStats1);

    EXPECT_CALL(*fileAccess, write(filepath, "words"));
    EXPECT_CALL(*serializer, serialize(twoWordsStatistics)).WillOnce(Return("words"));

    persistentStorage.addWordStatistics(wordStats2);

    ASSERT_EQ(persistentStorage.size(), 2);
}

TEST_F(StatisticsPersistentStorageTest, givenExistingInStorageEnglishWord_shouldReturnThisWordsStats)
{
    expectTwoWordStatisticsLoad();
    StatisticsPersistentStorage persistentStorage{fileAccess, serializer};

    const auto actualWordStats = persistentStorage.getWordStatistics(englishWord1);

    ASSERT_EQ(*actualWordStats, wordStats1);
}

TEST_F(StatisticsPersistentStorageTest, givenTwoWordsStats_shouldContainsThoseTwoWordsStats)
{
    expectTwoWordStatisticsLoad();
    StatisticsPersistentStorage persistentStorage{fileAccess, serializer};

    ASSERT_TRUE(persistentStorage.contains(englishWord1));
    ASSERT_TRUE(persistentStorage.contains(englishWord2));
    ASSERT_FALSE(persistentStorage.contains(nonExistingWord));
}

TEST_F(StatisticsPersistentStorageTest, givenCorrectAnswer_shouldIncreaseCorrectAnswersAndSerialize)
{
    expectOneWordStatisticsLoad();
    StatisticsPersistentStorage persistentStorage{fileAccess, serializer};
    EXPECT_CALL(*fileAccess, write(filepath, "words"));
    EXPECT_CALL(*serializer, serialize(oneWordStatisticsAfterCorrectAnswer)).WillOnce(Return("words"));

    persistentStorage.addCorrectAnswer(englishWord1);
}

TEST_F(StatisticsPersistentStorageTest, givenIncorrectAnswer_shouldIncreaseIncorrectAnswersAndSerialize)
{
    expectOneWordStatisticsLoad();
    StatisticsPersistentStorage persistentStorage{fileAccess, serializer};
    EXPECT_CALL(*fileAccess, write(filepath, "words"));
    EXPECT_CALL(*serializer, serialize(oneWordStatisticsAfterIncorrectAnswer)).WillOnce(Return("words"));

    persistentStorage.addIncorrectAnswer(englishWord1);
}

TEST_F(StatisticsPersistentStorageTest, shouldResetStatisticsAndSerialize)
{
    expectTwoWordStatisticsLoad();
    StatisticsPersistentStorage persistentStorage{fileAccess, serializer};
    EXPECT_CALL(*fileAccess, write(filepath, "words"));
    EXPECT_CALL(*serializer, serialize(twoResetWordsStatistics)).WillOnce(Return("words"));

    persistentStorage.resetStatistics();
}
