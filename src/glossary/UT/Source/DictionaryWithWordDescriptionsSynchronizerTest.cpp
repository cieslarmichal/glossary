#include "DictionaryWithWordDescriptionsSynchronizer.h"

#include "gtest/gtest.h"

#include "WordDescriptionLoaderMock.h"
#include "dictionaryService/DictionaryServiceMock.h"

using namespace ::testing;
using namespace glossary;
using namespace dictionaryService;

namespace
{
const DictionaryName dictionaryName{"dictionaryName"};
const DictionaryName nonExistingDictionaryName{"nonExisting"};
const std::string englishWord1{"englishWord1"};
const std::string englishWord2{"englishWord2"};
const std::string englishWord3{"englishWord2"};
const EnglishWords emptyEnglishWords{};
const EnglishWords englishWords{englishWord1, englishWord2, englishWord3};
}

class DictionaryWithWordDescriptionsSynchronizerTest : public Test
{
public:
    std::shared_ptr<dictionaryService::DictionaryServiceMock> dictionaryService =
        std::make_shared<StrictMock<dictionaryService::DictionaryServiceMock>>();
    std::shared_ptr<WordDescriptionLoaderMock> wordDescriptionLoader =
        std::make_shared<StrictMock<WordDescriptionLoaderMock>>();
    DictionaryWithWordDescriptionsSynchronizer synchronizer{dictionaryService, wordDescriptionLoader};
};

TEST_F(DictionaryWithWordDescriptionsSynchronizerTest,
       givenNonExistingDictionaryName_shouldNotLoadWordDescriptions)
{
    EXPECT_CALL(*dictionaryService, getEnglishWords(nonExistingDictionaryName)).WillOnce(Return(boost::none));

    synchronizer.synchronizeDictionary(nonExistingDictionaryName);
}

TEST_F(DictionaryWithWordDescriptionsSynchronizerTest,
       givenDictionaryWithEmptyWords_shouldNotLoadWordDescriptions)
{
    EXPECT_CALL(*dictionaryService, getEnglishWords(dictionaryName)).WillOnce(Return(emptyEnglishWords));

    synchronizer.synchronizeDictionary(dictionaryName);
}

TEST_F(DictionaryWithWordDescriptionsSynchronizerTest,
       givenDictionaryWordsFromDictionary_shouldLoadWordDescriptions)
{
    EXPECT_CALL(*dictionaryService, getEnglishWords(dictionaryName)).WillOnce(Return(englishWords));
    EXPECT_CALL(*wordDescriptionLoader, loadWordsDescriptions(englishWords));

    synchronizer.synchronizeDictionary(dictionaryName);
}

TEST_F(DictionaryWithWordDescriptionsSynchronizerTest,
       givenDictionariesWithEmptyWords_shouldNotLoadWordDescriptions)
{
    EXPECT_CALL(*dictionaryService, getEnglishWords()).WillOnce(Return(emptyEnglishWords));

    synchronizer.synchronizeDictionaries();
}

TEST_F(DictionaryWithWordDescriptionsSynchronizerTest,
       givenDictionaryWordsFromDictionaries_shouldLoadWordDescriptions)
{
    EXPECT_CALL(*dictionaryService, getEnglishWords()).WillOnce(Return(englishWords));
    EXPECT_CALL(*wordDescriptionLoader, loadWordsDescriptions(englishWords));

    synchronizer.synchronizeDictionaries();
}
