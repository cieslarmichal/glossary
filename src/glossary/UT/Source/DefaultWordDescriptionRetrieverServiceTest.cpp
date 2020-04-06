#include "DefaultWordDescriptionRetrieverService.h"

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
    std::shared_ptr<WordDescriptionDownloaderMock> wordDescriptionDownloader =
        std::make_shared<StrictMock<WordDescriptionDownloaderMock>>();
    std::shared_ptr<WordDescriptionRepositoryMock> wordDescriptionRepository =
        std::make_shared<StrictMock<WordDescriptionRepositoryMock>>();
    DefaultWordDescriptionRetrieverService wordDescriptionService{wordDescriptionDownloader,
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
