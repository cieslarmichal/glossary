#include "DefaultDictionaryService.h"

#include "gtest/gtest.h"

#include "DictionaryObserverMock.h"
#include "DictionaryWordsCsvReaderMock.h"
#include "ObserverServiceMock.h"
#include "random/RandomNumberGeneratorMock.h"
#include "repositories/DictionaryRepositoryMock.h"

using namespace ::testing;
using namespace glossary::dictionary;

namespace
{
const std::string absoluteDictionaryWordsPath{"absolutePathToDictionaryWords.csv"};
const std::string dictionaryName1{"dictionaryName1"};
const std::string dictionaryName2{"dictionaryName2"};
const std::string dictionaryName3{"dictionaryName3"};
const std::string nonExistingDictionaryName{"nonExisting"};
const DictionaryWord dictionaryWord1{"englishWord1", std::string{"translation1"}};
const DictionaryWord dictionaryWord2{"englishWord2", std::string{"translation2"}};
const DictionaryWord dictionaryWord3{"englishWord3", std::nullopt};
const DictionaryWord dictionaryWord4{"englishWord4", std::string{"translation4"}};
const DictionaryWord dictionaryWord5{"englishWord5", std::string{"translation5"}};
const std::vector<DictionaryWord> dictionaryWords1{dictionaryWord1, dictionaryWord2, dictionaryWord3};
const std::vector<DictionaryWord> dictionaryWords2{dictionaryWord4, dictionaryWord5};
const std::vector<DictionaryWord> emptyDictionaryWords{};
const Dictionary dictionary1{dictionaryName1, dictionaryWords1};
const Dictionary dictionary2{dictionaryName2, dictionaryWords2};
const Dictionary emptyDictionary{dictionaryName3, emptyDictionaryWords};
const std::vector<Dictionary> dictionaries{dictionary1, dictionary2, emptyDictionary};
const std::vector<std::string> dictionaryNames{dictionaryName1, dictionaryName2, dictionaryName3};
const std::vector<std::string> englishWordsFromDictionary1{dictionaryWord1.englishWord, dictionaryWord2.englishWord,
                                                           dictionaryWord3.englishWord};
const std::vector<std::string> englishWordsFromAllDictionaries{dictionaryWord1.englishWord, dictionaryWord2.englishWord,
                                                               dictionaryWord3.englishWord, dictionaryWord4.englishWord,
                                                               dictionaryWord5.englishWord};
const std::string newDictionaryWordTranslation{"newDictionaryWordTranslation"};
const std::string englishWord{"englishWord1"};
const std::string englishWordTranslation{"translation2"};
}

class DefaultDictionaryServiceTest : public Test
{
public:
    std::shared_ptr<DictionaryObserverMock> observer = std::make_shared<StrictMock<DictionaryObserverMock>>();

    std::shared_ptr<DictionaryRepositoryMock> dictionaryRepository =
        std::make_shared<StrictMock<DictionaryRepositoryMock>>();

    std::unique_ptr<DictionaryWordsCsvReaderMock> readerInit =
        std::make_unique<StrictMock<DictionaryWordsCsvReaderMock>>();
    DictionaryWordsCsvReaderMock* reader = readerInit.get();

    std::unique_ptr<ObserverServiceMock> observerServiceInit = std::make_unique<StrictMock<ObserverServiceMock>>();
    ObserverServiceMock* observerService = observerServiceInit.get();

    std::shared_ptr<common::random::RandomNumberGeneratorMock> randomNumberGenerator =
        std::make_shared<StrictMock<common::random::RandomNumberGeneratorMock>>();

    DefaultDictionaryService service{dictionaryRepository, std::move(readerInit), std::move(observerServiceInit),
                                     randomNumberGenerator};
};

TEST_F(DefaultDictionaryServiceTest, shouldReturnDictionary)
{
    EXPECT_CALL(*dictionaryRepository, getDictionary(dictionaryName1)).WillOnce(Return(dictionary1));

    const auto actualDictionary = service.getDictionary(dictionaryName1);

    ASSERT_EQ(actualDictionary, dictionary1);
}

TEST_F(DefaultDictionaryServiceTest, shouldReturnDictionaries)
{
    EXPECT_CALL(*dictionaryRepository, getDictionaries()).WillOnce(Return(dictionaries));

    const auto actualDictionaries = service.getDictionaries();

    ASSERT_EQ(actualDictionaries, dictionaries);
}

TEST_F(DefaultDictionaryServiceTest, shouldReturnDictionaryNames)
{
    EXPECT_CALL(*dictionaryRepository, getDictionaries()).WillOnce(Return(dictionaries));

    const auto actualDictionaryNames = service.getDictionaryNames();

    ASSERT_EQ(actualDictionaryNames, dictionaryNames);
}

TEST_F(DefaultDictionaryServiceTest, shouldReturnDictionaryWords)
{
    EXPECT_CALL(*dictionaryRepository, getDictionary(dictionaryName1)).WillOnce(Return(dictionary1));

    const auto actualDictionaryWords = service.getDictionaryWords(dictionaryName1);

    ASSERT_EQ(*actualDictionaryWords, dictionaryWords1);
}

TEST_F(DefaultDictionaryServiceTest, shouldReturnEnglishWordsFromDictionary)
{
    EXPECT_CALL(*dictionaryRepository, getDictionary(dictionaryName1)).WillOnce(Return(dictionary1));

    const auto actualEnglishWords = service.getEnglishWords(dictionaryName1);

    ASSERT_EQ(*actualEnglishWords, englishWordsFromDictionary1);
}

TEST_F(DefaultDictionaryServiceTest, givenNoDictionaryFromRepository_shouldReturnNone)
{
    EXPECT_CALL(*dictionaryRepository, getDictionary(dictionaryName1)).WillOnce(Return(std::nullopt));

    const auto actualEnglishWords = service.getEnglishWords(dictionaryName1);

    ASSERT_EQ(actualEnglishWords, std::nullopt);
}

TEST_F(DefaultDictionaryServiceTest, shouldReturnEnglishWordsFromDictionaries)
{
    EXPECT_CALL(*dictionaryRepository, getDictionaries()).WillOnce(Return(dictionaries));

    const auto actualEnglishWords = service.getEnglishWords();

    ASSERT_EQ(actualEnglishWords, englishWordsFromAllDictionaries);
}

TEST_F(DefaultDictionaryServiceTest, givenDictionaryName_shouldReturnRandomDictionaryWordFromThisDictionary)
{
    EXPECT_CALL(*dictionaryRepository, getDictionary(dictionaryName1)).WillOnce(Return(dictionary1));

    EXPECT_CALL(*randomNumberGenerator, generate(0, dictionary1.words.size() - 1)).WillOnce(Return(0));

    const auto actualRandomizedDictionaryWord = service.getRandomDictionaryWord(dictionaryName1);

    ASSERT_EQ(*actualRandomizedDictionaryWord, dictionaryWord1);
}

TEST_F(DefaultDictionaryServiceTest, givenDictionaries_shouldReturnRandomDictionaryWord)
{
    EXPECT_CALL(*dictionaryRepository, getDictionaries()).WillOnce(Return(dictionaries));

    EXPECT_CALL(*randomNumberGenerator, generate(0, 4)).WillOnce(Return(1));

    const auto actualRandomizedDictionaryWord = service.getRandomDictionaryWord();

    ASSERT_EQ(*actualRandomizedDictionaryWord, dictionaryWord2);
}

TEST_F(DefaultDictionaryServiceTest, shouldAddDictionaryByName)
{
    EXPECT_CALL(*dictionaryRepository, addDictionary(dictionaryName1));

    service.addDictionary(dictionaryName1);
}

TEST_F(DefaultDictionaryServiceTest, givenDictionaryWordsFromFile_shouldAddDictionary)
{
    EXPECT_CALL(*reader, readDictionaryWords(absoluteDictionaryWordsPath)).WillOnce(Return(dictionaryWords1));

    EXPECT_CALL(*dictionaryRepository, addDictionary(dictionary1));

    EXPECT_CALL(*dictionaryRepository, getDictionary(dictionaryName1)).WillOnce(Return(dictionary1));

    EXPECT_CALL(*observerService, notifyObservers(englishWordsFromDictionary1));

    service.addDictionaryFromFile(dictionaryName1, absoluteDictionaryWordsPath);
}

TEST_F(DefaultDictionaryServiceTest, shouldAddWordToDictionary)
{
    EXPECT_CALL(*dictionaryRepository, addWordToDictionary(dictionaryWord3, dictionaryName1));

    service.addWordToDictionary(dictionaryWord3, dictionaryName1);
}

TEST_F(DefaultDictionaryServiceTest, shouldRemoveDictionary)
{
    EXPECT_CALL(*dictionaryRepository, removeDictionary(dictionaryName1));

    service.removeDictionary(dictionaryName1);
}

TEST_F(DefaultDictionaryServiceTest, shouldRemoveWordFromDictionary)
{
    EXPECT_CALL(*dictionaryRepository, removeWordFromDictionary(dictionaryWord1.englishWord, dictionaryName1));

    service.removeWordFromDictionary(dictionaryWord1.englishWord, dictionaryName1);
}

TEST_F(DefaultDictionaryServiceTest, shouldUpdateWordTranslationFromDictionary)
{
    EXPECT_CALL(*dictionaryRepository, changeWordTranslationFromDictionary(
                                           dictionaryWord1.englishWord, newDictionaryWordTranslation, dictionaryName1));

    service.updateWordTranslationFromDictionary(dictionaryWord1.englishWord, newDictionaryWordTranslation,
                                                dictionaryName1);
}

TEST_F(DefaultDictionaryServiceTest, synchronizeDictionaries_shouldNotifyObserversAboutAllDictionaryEnglishWords)
{
    EXPECT_CALL(*dictionaryRepository, getDictionaries()).WillOnce(Return(dictionaries));

    EXPECT_CALL(*observerService, notifyObservers(englishWordsFromAllDictionaries));

    service.synchronizeDictionaries();
}

TEST_F(DefaultDictionaryServiceTest, shouldAddObserver)
{
    EXPECT_CALL(*observerService, registerObserver(observer.get()));

    service.registerObserver(observer.get());
}

TEST_F(DefaultDictionaryServiceTest, shouldRemoveObserver)
{
    EXPECT_CALL(*observerService, removeObserver(observer.get()));

    service.removeObserver(observer.get());
}
