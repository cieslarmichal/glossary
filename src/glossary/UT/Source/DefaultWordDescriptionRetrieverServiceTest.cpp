#include "DefaultWordDescriptionRetrieverService.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "wordDescriptionDownloader/WordDescriptionDownloaderMock.h"
#include "wordDescriptionRepository/WordDescriptionRepositoryMock.h"

using namespace ::testing;
using namespace glossary;
using namespace wordDescriptionRepository;
using namespace wordDescriptionDownloader;

namespace
{
const EnglishWord englishWord{"englishWord1"};
const WordDescription wordDescriptionFromRepository{englishWord, {{{"def1", boost::none}}, {}}};
const WordDescription wordDescriptionFromDownloader{englishWord, {{{"def2", boost::none}}, {}}};
const WordDescription emptyWordDescription{englishWord, {}};
}

class DefaultWordDescriptionRetrieverServiceTest : public Test
{
public:
    std::unique_ptr<WordDescriptionDownloaderMock> wordDescriptionDownloaderInit =
        std::make_unique<StrictMock<WordDescriptionDownloaderMock>>();
    WordDescriptionDownloaderMock* wordDescriptionDownloader = wordDescriptionDownloaderInit.get();
    std::shared_ptr<WordDescriptionRepositoryMock> wordDescriptionRepository =
        std::make_shared<StrictMock<WordDescriptionRepositoryMock>>();
    DefaultWordDescriptionRetrieverService wordDescriptionService{std::move(wordDescriptionDownloaderInit),
                                                                  wordDescriptionRepository};
};

TEST_F(DefaultWordDescriptionRetrieverServiceTest,
       repositoryContainsWordDescription_shouldReturnWordDescriptionFromRepository)
{
    EXPECT_CALL(*wordDescriptionRepository, getWordDescription(englishWord))
        .WillOnce(Return(wordDescriptionFromRepository));

    const auto actualWordDescription = wordDescriptionService.retrieveWordDescription(englishWord);

    ASSERT_EQ(actualWordDescription, wordDescriptionFromRepository);
}

TEST_F(
    DefaultWordDescriptionRetrieverServiceTest,
    RepositoryDoesNotContainWordDescription_shouldReturnWordDescriptionFromDownloaderAndSaveWordDescriptionInRepository)
{
    EXPECT_CALL(*wordDescriptionRepository, getWordDescription(englishWord)).WillOnce(Return(boost::none));
    EXPECT_CALL(*wordDescriptionDownloader, downloadWordDescription(englishWord))
        .WillOnce(Return(wordDescriptionFromDownloader));
    EXPECT_CALL(*wordDescriptionRepository, addWordDescription(wordDescriptionFromDownloader));

    const auto actualWordDescription = wordDescriptionService.retrieveWordDescription(englishWord);

    ASSERT_EQ(actualWordDescription, wordDescriptionFromDownloader);
}

TEST_F(DefaultWordDescriptionRetrieverServiceTest,
       repositoryAndDownloaderDoNotRespondWithWordDescription_shouldReturnEmptyWordDescriptionWithEnglishWord)
{
    EXPECT_CALL(*wordDescriptionRepository, getWordDescription(englishWord)).WillOnce(Return(boost::none));
    EXPECT_CALL(*wordDescriptionDownloader, downloadWordDescription(englishWord))
        .WillOnce(Return(boost::none));
    EXPECT_CALL(*wordDescriptionRepository, addWordDescription(emptyWordDescription));

    const auto actualWordDescription = wordDescriptionService.retrieveWordDescription(englishWord);

    ASSERT_EQ(actualWordDescription, emptyWordDescription);
}
