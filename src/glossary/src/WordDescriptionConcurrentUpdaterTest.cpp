#include "WordDescriptionConcurrentUpdater.h"

#include "gtest/gtest.h"

#include "wordDescriptionDownloader/WordDescriptionDownloaderMock.h"
#include "wordDescriptionRepository/WordDescriptionRepositoryMock.h"
#include "webConnection/exceptions/ConnectionFailed.h"
#include "wordDescriptionDownloader/exceptions/InvalidApiKey.h"

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
const WordDescription wordDescription1{englishWord1, {}, {}, {}};
}

class WordDescriptionConcurrentUpdaterTest : public Test
{
public:
    std::shared_ptr<WordDescriptionDownloaderMock> wordDescriptionDownloader =
        std::make_shared<StrictMock<WordDescriptionDownloaderMock>>();
    std::shared_ptr<WordDescriptionRepositoryMock> wordDescriptionRepository =
        std::make_shared<StrictMock<WordDescriptionRepositoryMock>>();
    WordDescriptionConcurrentUpdater updater{wordDescriptionDownloader, wordDescriptionRepository};
};

TEST_F(WordDescriptionConcurrentUpdaterTest, givenEnglishWordsExistingInRepository_shouldNotLoadAnything)
{
    EXPECT_CALL(*wordDescriptionRepository, contains(englishWord1)).WillOnce(Return(true));
    EXPECT_CALL(*wordDescriptionRepository, contains(englishWord2)).WillOnce(Return(true));
    EXPECT_CALL(*wordDescriptionRepository, contains(englishWord3)).WillOnce(Return(true));

    updater.update(englishWords);
}

TEST_F(WordDescriptionConcurrentUpdaterTest,
       givenEnglishWordsNonExistingInRepository_shouldDownloadWordDescriptionsAndAddToRepositoryIfExists)
{
    EXPECT_CALL(*wordDescriptionRepository, contains(englishWord1)).WillOnce(Return(false));
    EXPECT_CALL(*wordDescriptionRepository, contains(englishWord2)).WillOnce(Return(false));
    EXPECT_CALL(*wordDescriptionRepository, contains(englishWord3)).WillOnce(Return(false));

    EXPECT_CALL(*wordDescriptionDownloader, tryDownloadWordDescription(englishWord1))
        .WillOnce(Return(wordDescription1));
    EXPECT_CALL(*wordDescriptionDownloader, tryDownloadWordDescription(englishWord2))
        .WillOnce(Throw(webConnection::exceptions::ConnectionFailed{""}));
    EXPECT_CALL(*wordDescriptionDownloader, tryDownloadWordDescription(englishWord3))
        .WillOnce(Throw(wordDescriptionDownloader::exceptions::InvalidApiKey{""}));

    EXPECT_CALL(*wordDescriptionRepository, addWordDescription(wordDescription1));

    updater.update(englishWords);
}
