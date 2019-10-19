#include "PersistentAnswersCounter.h"

#include "gtest/gtest.h"
#include "FileAccessMock.h"
#include "AnswersStatisticsSerializerMock.h"
#include "Exceptions/FileNotFound.h"
#include "boost/assign.hpp"

using namespace ::testing;

namespace
{
const std::string filePath{"../database/answersStatistics.txt"};
const AnswersStatisticsPerWord statisticsPerWord1{EnglishWord{"cat"}, 7, 0};
const AnswersStatisticsPerWord statisticsPerWord2{EnglishWord{"dog"}, 2, 1};
const AnswersStatistics answersStatistics = boost::assign::map_list_of
        (statisticsPerWord1.englishWord, statisticsPerWord1)
        (statisticsPerWord2.englishWord, statisticsPerWord2);
const AnswersStatistics answersStatisticsWithWord1 = boost::assign::map_list_of
        (statisticsPerWord1.englishWord, statisticsPerWord1);
const AnswersStatisticsPerWord statisticsPerWord1AfterCorrectAnswer{EnglishWord{"cat"}, 8, 0};
const AnswersStatisticsPerWord statisticsPerWord1AfterIncorrectAnswer{EnglishWord{"cat"}, 7, 1};
const AnswersStatistics answersStatisticsWithWord1AfterCorrectAnswer{{statisticsPerWord1AfterCorrectAnswer.englishWord, statisticsPerWord1AfterCorrectAnswer}};
const AnswersStatistics answersStatisticsWithWord1AfterIncorrectAnswer{{statisticsPerWord1AfterIncorrectAnswer.englishWord, statisticsPerWord1AfterIncorrectAnswer}};
const std::string serializedStatisticsAfterCorrectAddition{
        R"({"answersStatistics":[{"correctAnswers":8,"englishWord":"cat","incorrectAnswers":0}]})"};
const std::string serializedStatisticsAfterIncorrectAddition{
        R"({"answersStatistics":[{"correctAnswers":7,"englishWord":"cat","incorrectAnswers":1}]})"};
}

class PersistentAnswersCounterTest : public Test
{
public:
    std::shared_ptr<FileAccessMock> fileAccess = std::make_shared<StrictMock<FileAccessMock>>();
    std::shared_ptr<AnswersStatisticsSerializerMock> serializer = std::make_shared<StrictMock<AnswersStatisticsSerializerMock>>();
};

TEST_F(PersistentAnswersCounterTest, givenEmptyFile_shouldNotLoadAnyStatistics)
{
    EXPECT_CALL(*fileAccess, readContent(filePath)).WillOnce(Return(""));
    EXPECT_CALL(*serializer, deserialize("")).WillOnce(Return(AnswersStatistics{}));
    PersistentAnswersCounter answersCounter{fileAccess, serializer};

    const auto actualStatistics = answersCounter.getAnswersStatistics();

    ASSERT_TRUE(actualStatistics.empty());
}

TEST_F(PersistentAnswersCounterTest, givenPersistentStorageWithFileWithWords_shouldLoadWords)
{
    EXPECT_CALL(*fileAccess, readContent(filePath)).WillOnce(Return("some content"));
    EXPECT_CALL(*serializer, deserialize("some content")).WillOnce(Return(answersStatistics));
    PersistentAnswersCounter answersCounter{fileAccess, serializer};

    const auto actualStatistics = answersCounter.getAnswersStatistics();

    ASSERT_EQ(actualStatistics, answersStatistics);
}

TEST_F(PersistentAnswersCounterTest, givenInvalidFile_shouldReturnNoStatictics)
{
    EXPECT_CALL(*fileAccess, readContent(filePath)).WillOnce(Throw(exceptions::FileNotFound{""}));
    PersistentAnswersCounter answersCounter{fileAccess, serializer};

    const auto actualStatistics = answersCounter.getAnswersStatistics();

    EXPECT_TRUE(actualStatistics.empty());
}

TEST_F(PersistentAnswersCounterTest, givenCorrectAnswer_shouldIncreaseCorrectAnswersInStatisticsAndSerializeToFile)
{
    EXPECT_CALL(*fileAccess, readContent(filePath)).WillOnce(Return("some content"));
    EXPECT_CALL(*serializer, deserialize("some content")).WillOnce(Return(answersStatisticsWithWord1));
    PersistentAnswersCounter answersCounter{fileAccess, serializer};

    EXPECT_CALL(*serializer, serialize(answersStatisticsWithWord1AfterCorrectAnswer)).WillOnce(
            Return(serializedStatisticsAfterCorrectAddition));
    EXPECT_CALL(*fileAccess, write(filePath, serializedStatisticsAfterCorrectAddition));

    answersCounter.addCorrectAnswer(statisticsPerWord1.englishWord);

    const auto actualStatisticsPerWord1 = answersCounter.getAnswersStatisticsPerWord(statisticsPerWord1.englishWord);
    ASSERT_EQ(actualStatisticsPerWord1, statisticsPerWord1AfterCorrectAnswer);
}

TEST_F(PersistentAnswersCounterTest, givenIncorrectAnswer_shouldIncreaseIncorrectAnswersInStatisticsAndSerializeToFile)
{
    EXPECT_CALL(*fileAccess, readContent(filePath)).WillOnce(Return("some content"));
    EXPECT_CALL(*serializer, deserialize("some content")).WillOnce(Return(answersStatisticsWithWord1));
    PersistentAnswersCounter answersCounter{fileAccess, serializer};

    EXPECT_CALL(*serializer, serialize(answersStatisticsWithWord1AfterIncorrectAnswer)).WillOnce(
            Return(serializedStatisticsAfterIncorrectAddition));
    EXPECT_CALL(*fileAccess, write(filePath, serializedStatisticsAfterIncorrectAddition));
    answersCounter.addIncorrectAnswer(statisticsPerWord1.englishWord);

    const auto actualStatisticsPerWord1 = answersCounter.getAnswersStatisticsPerWord(statisticsPerWord1.englishWord);
    ASSERT_EQ(actualStatisticsPerWord1, statisticsPerWord1AfterIncorrectAnswer);
}
