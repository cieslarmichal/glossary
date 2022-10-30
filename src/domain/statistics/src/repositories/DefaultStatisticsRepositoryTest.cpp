#include "DefaultStatisticsRepository.h"



#include "gtest/gtest.h"

#include "StatisticsStorageMock.h"

using namespace ::testing;
using namespace glossary::statistics;

namespace
{
const std::string englishWord1{"englishWord1"};
const std::string englishWord2{"englishWord2"};
const std::string nonExistingWord{"nonExistingWord"};
const WordStatistics wordStats1{englishWord1, 7, 0};
const WordStatistics wordStats2{englishWord2, 8, 0};
const std::vector<WordStatistics> oneWordStatistics{wordStats1};
const std::vector<WordStatistics> twoWordsStatistics{wordStats1, wordStats2};
}

class DefaultStatisticsRepositoryTest : public Test
{
public:
    std::unique_ptr<StatisticsStorageMock> storageInit =
        std::make_unique<StrictMock<StatisticsStorageMock>>();
    StatisticsStorageMock* storage = storageInit.get();
    DefaultStatisticsRepository repository{std::move(storageInit)};
};

TEST_F(DefaultStatisticsRepositoryTest, addWordStatistics)
{
    EXPECT_CALL(*storage, addWordStatistics(wordStats1));

    repository.addWordStatistics(wordStats1);
}

TEST_F(DefaultStatisticsRepositoryTest, getWordStatistics)
{
    EXPECT_CALL(*storage, getWordStatistics(englishWord1)).WillOnce(Return(wordStats1));

    const auto actualWordStats = repository.getWordStatistics(englishWord1);

    ASSERT_EQ(actualWordStats, wordStats1);
}

TEST_F(DefaultStatisticsRepositoryTest, getStatistics)
{
    EXPECT_CALL(*storage, getStatistics()).WillOnce(Return(twoWordsStatistics));

    const auto statistics = repository.getStatistics();

    ASSERT_EQ(statistics, twoWordsStatistics);
}

TEST_F(DefaultStatisticsRepositoryTest, englishWordInStorage_shouldAddCorrectAnswer)
{
    EXPECT_CALL(*storage, contains(englishWord1)).WillOnce(Return(true));
    EXPECT_CALL(*storage, addCorrectAnswer(englishWord1));

    repository.addCorrectAnswer(englishWord1);
}

TEST_F(DefaultStatisticsRepositoryTest, englishWordNotInStorage_shouldAddEmptyWordAndThenAddCorrectAnswer)
{
    EXPECT_CALL(*storage, contains(englishWord1)).WillOnce(Return(false));
    EXPECT_CALL(*storage, addWordStatistics(WordStatistics{englishWord1, 0, 0}));
    EXPECT_CALL(*storage, addCorrectAnswer(englishWord1));

    repository.addCorrectAnswer(englishWord1);
}

TEST_F(DefaultStatisticsRepositoryTest, englishWordInStorage_shouldAddIncorrectAnswer)
{
    EXPECT_CALL(*storage, contains(englishWord1)).WillOnce(Return(true));
    EXPECT_CALL(*storage, addIncorrectAnswer(englishWord1));

    repository.addIncorrectAnswer(englishWord1);
}

TEST_F(DefaultStatisticsRepositoryTest, englishWordNotInStorage_shouldAddEmptyWordAndThenAddIncorrectAnswer)
{
    EXPECT_CALL(*storage, contains(englishWord1)).WillOnce(Return(false));
    EXPECT_CALL(*storage, addWordStatistics(WordStatistics{englishWord1, 0, 0}));
    EXPECT_CALL(*storage, addIncorrectAnswer(englishWord1));

    repository.addIncorrectAnswer(englishWord1);
}

TEST_F(DefaultStatisticsRepositoryTest, resetStatistics)
{
    EXPECT_CALL(*storage, resetStatistics());

    repository.resetStatistics();
}
