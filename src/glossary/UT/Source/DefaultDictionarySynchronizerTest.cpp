#include "DefaultDictionarySynchronizer.h"

#include "gtest/gtest.h"

#include "TranslationLoaderMock.h"
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

class DefaultDictionarySynchronizerTest : public Test
{
public:
    std::shared_ptr<dictionaryService::DictionaryServiceMock> dictionaryService =
        std::make_shared<StrictMock<dictionaryService::DictionaryServiceMock>>();
    std::shared_ptr<WordDescriptionLoaderMock> wordDescriptionLoader =
        std::make_shared<StrictMock<WordDescriptionLoaderMock>>();
    std::shared_ptr<TranslationLoaderMock> translationLoader =
        std::make_shared<StrictMock<TranslationLoaderMock>>();
    DefaultDictionarySynchronizer synchronizer{dictionaryService, wordDescriptionLoader, translationLoader};
};

TEST_F(DefaultDictionarySynchronizerTest, givenNonExistingDictionaryName_shouldNotLoadAnything)
{
    EXPECT_CALL(*dictionaryService, getEnglishWords(nonExistingDictionaryName)).WillOnce(Return(boost::none));

    synchronizer.synchronizeDictionary(nonExistingDictionaryName);
}

TEST_F(DefaultDictionarySynchronizerTest, givenDictionaryWithEmptyWords_shouldNotLoadAnything)
{
    EXPECT_CALL(*dictionaryService, getEnglishWords(dictionaryName)).WillOnce(Return(emptyEnglishWords));

    synchronizer.synchronizeDictionary(dictionaryName);
}

TEST_F(DefaultDictionarySynchronizerTest,
       givenDictionaryWordsFromDictionary_shouldLoadWordDescriptionsAndTranslations)
{
    EXPECT_CALL(*dictionaryService, getEnglishWords(dictionaryName)).WillOnce(Return(englishWords));
    EXPECT_CALL(*wordDescriptionLoader, loadMissingWordsDescriptions(englishWords));
    EXPECT_CALL(*translationLoader, loadMissingTranslations(englishWords));

    synchronizer.synchronizeDictionary(dictionaryName);
}

TEST_F(DefaultDictionarySynchronizerTest, givenDictionariesWithEmptyWords_shouldNotLoadAnything)
{
    EXPECT_CALL(*dictionaryService, getEnglishWords()).WillOnce(Return(emptyEnglishWords));

    synchronizer.synchronizeDictionaries();
}

TEST_F(DefaultDictionarySynchronizerTest,
       givenDictionaryWordsFromDictionaries_shouldLoadWordDescriptionsAndTranslations)
{
    EXPECT_CALL(*dictionaryService, getEnglishWords()).WillOnce(Return(englishWords));
    EXPECT_CALL(*wordDescriptionLoader, loadMissingWordsDescriptions(englishWords));
    EXPECT_CALL(*translationLoader, loadMissingTranslations(englishWords));

    synchronizer.synchronizeDictionaries();
}
