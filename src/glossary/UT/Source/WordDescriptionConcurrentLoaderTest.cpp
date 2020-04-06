#include "WordDescriptionConcurrentLoader.h"

#include "gtest/gtest.h"

#include "wordDescriptionDownloader/WordDescriptionDownloaderMock.h"
#include "wordDescriptionRepository/WordDescriptionRepositoryMock.h"

using namespace ::testing;
using namespace glossary;
using namespace wordDescriptionRepository;
using namespace wordDescriptionDownloader;

namespace
{
const EnglishWord englishWord1{"englishWord1"};
const EnglishWord englishWord2{"englishWord2"};
const EnglishWord englishWord3{"englishWord3"};
const EnglishWords englishWords{englishWord1, englishWord2, englishWord3};
const WordDescription wordDescription1{englishWord1, Description{}};
const WordDescription wordDescription2{
    englishWord2,
    Description{DefinitionsWithExamples{DefinitionWithExample{Definition{"definition"}, Example{"example"}}},
                {}}};
const WordDescription wordDescription3{englishWord3, Description{}};
const WordsDescriptions expectedWordsDescriptions{wordDescription1, wordDescription2, wordDescription3};
}

class WordDescriptionConcurrentLoaderTest : public Test
{
public:
    std::shared_ptr<WordDescriptionDownloaderMock> wordDescriptionDownloader =
        std::make_shared<StrictMock<WordDescriptionDownloaderMock>>();
    std::shared_ptr<WordDescriptionRepositoryMock> wordDescriptionRepository =
        std::make_shared<StrictMock<WordDescriptionRepositoryMock>>();
    WordDescriptionConcurrentLoader loader{wordDescriptionDownloader, wordDescriptionRepository};
};

TEST_F(WordDescriptionConcurrentLoaderTest, givenEnglishWordsExistingInRepository_shouldNotLoadAnything)
{
    EXPECT_CALL(*wordDescriptionRepository, contains(englishWord1)).WillOnce(Return(true));
    EXPECT_CALL(*wordDescriptionRepository, contains(englishWord2)).WillOnce(Return(true));
    EXPECT_CALL(*wordDescriptionRepository, contains(englishWord3)).WillOnce(Return(true));

    loader.loadWordsDescriptions(englishWords);
}

TEST_F(WordDescriptionConcurrentLoaderTest,
       givenEnglishWordsNonExistingInRepository_shouldDownloadWordDescriptionsAndAddToRepositoryIfExists)
{
    EXPECT_CALL(*wordDescriptionRepository, contains(englishWord1)).WillOnce(Return(false));
    EXPECT_CALL(*wordDescriptionRepository, contains(englishWord2)).WillOnce(Return(false));
    EXPECT_CALL(*wordDescriptionRepository, contains(englishWord3)).WillOnce(Return(false));

    EXPECT_CALL(*wordDescriptionDownloader, downloadWordDescription(englishWord1))
        .WillOnce(Return(wordDescription1));
    EXPECT_CALL(*wordDescriptionDownloader, downloadWordDescription(englishWord2))
        .WillOnce(Return(boost::none));
    EXPECT_CALL(*wordDescriptionDownloader, downloadWordDescription(englishWord3))
        .WillOnce(Return(boost::none));

    EXPECT_CALL(*wordDescriptionRepository, addWordDescription(wordDescription1));

    loader.loadWordsDescriptions(englishWords);
}
