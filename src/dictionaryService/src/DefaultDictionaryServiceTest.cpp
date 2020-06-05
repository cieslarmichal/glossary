#include "DefaultDictionaryService.h"

#include "gtest/gtest.h"

#include "DictionaryNamesRetrieverMock.h"
#include "DictionaryObserverMock.h"
#include "DictionaryWordsRetrieverMock.h"
#include "ObserverServiceMock.h"
#include "RandomDictionaryWordRetrieverMock.h"
#include "csvFileReading/DictionaryWordsReaderMock.h"
#include "repository/DictionaryRepositoryMock.h"

using namespace ::testing;
using namespace glossary::dictionaryService;

namespace
{
const std::string absoluteDictionaryWordsPath{"absoultePathToDictionaryWords.csv"};
const DictionaryName dictionaryName1{"dictionaryName1"};
const DictionaryName dictionaryName2{"dictionaryName2"};
const DictionaryName dictionaryName3{"dictionaryName3"};
const DictionaryName nonExistingDictionaryName{"nonExisting"};
const DictionaryWord dictionaryWord1{"englishWord1", std::string{"translation1"}};
const DictionaryWord dictionaryWord2{"englishWord2", std::string{"translation2"}};
const DictionaryWord dictionaryWord3{"englishWord3", boost::none};
const DictionaryWords dictionaryWords1{dictionaryWord1, dictionaryWord2, dictionaryWord3};
const DictionaryWords dictionaryWords2{dictionaryWord1, dictionaryWord2};
const DictionaryWords dictionaryWordsSum{dictionaryWord1, dictionaryWord2, dictionaryWord3, dictionaryWord1,
                                         dictionaryWord2};
const DictionaryWords emptyDictionaryWords{};
const Dictionary dictionary1{dictionaryName1, dictionaryWords1};
const Dictionary dictionary2{dictionaryName2, dictionaryWords2};
const Dictionary emptyDictionary{dictionaryName3, emptyDictionaryWords};
const Dictionaries dictionaries{dictionary1, dictionary2, emptyDictionary};
const DictionaryNames dictionaryNames{dictionaryName1, dictionaryName2, dictionaryName3};
const EnglishWords englishWords{dictionaryWord1.englishWord, dictionaryWord2.englishWord,
                                dictionaryWord3.englishWord};
const std::string newDictionaryWordTranslation{"newDictionaryWordTranslation"};
const std::string englishWord{"englishWord"};
const std::string englishWordTranslation{"englishWordTranslation"};
}

class DefaultDictionaryServiceTest : public Test
{
public:
    std::shared_ptr<DictionaryObserverMock> observer = std::make_shared<StrictMock<DictionaryObserverMock>>();

    std::shared_ptr<repository::DictionaryRepositoryMock> dictionaryRepository =
        std::make_shared<StrictMock<repository::DictionaryRepositoryMock>>();

    std::unique_ptr<DictionaryNamesRetrieverMock> namesRetrieverInit =
        std::make_unique<StrictMock<DictionaryNamesRetrieverMock>>();
    DictionaryNamesRetrieverMock* dictionaryNamesRetriever = namesRetrieverInit.get();

    std::unique_ptr<DictionaryWordsRetrieverMock> wordsRetrieverInit =
        std::make_unique<StrictMock<DictionaryWordsRetrieverMock>>();
    DictionaryWordsRetrieverMock* dictionaryWordsRetriever = wordsRetrieverInit.get();

    std::unique_ptr<RandomDictionaryWordRetrieverMock> randomWordRetrieverInit =
        std::make_unique<StrictMock<RandomDictionaryWordRetrieverMock>>();
    RandomDictionaryWordRetrieverMock* randomDictionaryWordRetriever = randomWordRetrieverInit.get();

    std::unique_ptr<csvFileReading::DictionaryWordsReaderMock> readerInit =
        std::make_unique<StrictMock<csvFileReading::DictionaryWordsReaderMock>>();
    csvFileReading::DictionaryWordsReaderMock* reader = readerInit.get();

    std::unique_ptr<ObserverServiceMock> observerServiceInit =
        std::make_unique<StrictMock<ObserverServiceMock>>();
    ObserverServiceMock* observerService = observerServiceInit.get();

    DefaultDictionaryService service{dictionaryRepository,          std::move(namesRetrieverInit),
                                     std::move(wordsRetrieverInit), std::move(randomWordRetrieverInit),
                                     std::move(readerInit),         std::move(observerServiceInit)};
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
    EXPECT_CALL(*dictionaryNamesRetriever, retrieveDictionaryNames()).WillOnce(Return(dictionaryNames));

    const auto actualDictionaryNames = service.getDictionaryNames();

    ASSERT_EQ(actualDictionaryNames, dictionaryNames);
}

TEST_F(DefaultDictionaryServiceTest, shouldReturnDictionaryNamesContainingEnglishWord)
{
    EXPECT_CALL(*dictionaryNamesRetriever, retrieveDictionaryNamesContainingEnglishWord(englishWord))
        .WillOnce(Return(dictionaryNames));

    const auto actualDictionaryNames = service.getDictionaryNamesContainingEnglishWord(englishWord);

    ASSERT_EQ(actualDictionaryNames, dictionaryNames);
}

TEST_F(DefaultDictionaryServiceTest, shouldReturnDictionaryNamesContainingEnglishWordTranslation)
{
    EXPECT_CALL(*dictionaryNamesRetriever,
                retrieveDictionaryNamesContainingEnglishWordTranslation(englishWordTranslation))
        .WillOnce(Return(dictionaryNames));

    const auto actualDictionaryNames =
        service.getDictionaryNamesContainingEnglishWordTranslation(englishWordTranslation);

    ASSERT_EQ(actualDictionaryNames, dictionaryNames);
}

TEST_F(DefaultDictionaryServiceTest, shouldReturnDictionaryWords)
{
    EXPECT_CALL(*dictionaryWordsRetriever, retrieveDictionaryWords(dictionaryName1))
        .WillOnce(Return(dictionaryWords1));

    const auto actualDictionaryWords = service.getDictionaryWords(dictionaryName1);

    ASSERT_EQ(*actualDictionaryWords, dictionaryWords1);
}

TEST_F(DefaultDictionaryServiceTest, shouldReturnEnglishWordsFromDictionary)
{
    EXPECT_CALL(*dictionaryWordsRetriever, retrieveEnglishWords(dictionaryName1))
        .WillOnce(Return(englishWords));

    const auto actualEnglishWords = service.getEnglishWords(dictionaryName1);

    ASSERT_EQ(*actualEnglishWords, englishWords);
}

TEST_F(DefaultDictionaryServiceTest, shouldReturnEnglishWordsFromDictionaries)
{
    EXPECT_CALL(*dictionaryWordsRetriever, retrieveEnglishWords()).WillOnce(Return(englishWords));

    const auto actualEnglishWords = service.getEnglishWords();

    ASSERT_EQ(actualEnglishWords, englishWords);
}

TEST_F(DefaultDictionaryServiceTest, givenDictionaryName_shouldReturnRandomDictionaryWordFromThisDictionary)
{
    EXPECT_CALL(*randomDictionaryWordRetriever, getRandomDictionaryWord(dictionaryName1))
        .WillOnce(Return(dictionaryWord1));

    const auto actualRandomizedDictionaryWord = service.getRandomDictionaryWord(dictionaryName1);

    ASSERT_EQ(*actualRandomizedDictionaryWord, dictionaryWord1);
}

TEST_F(DefaultDictionaryServiceTest, givenDictionaries_shouldReturnRandomDictionaryWord)
{
    EXPECT_CALL(*randomDictionaryWordRetriever, getRandomDictionaryWord()).WillOnce(Return(dictionaryWord2));

    const auto actualRandomizedDictionaryWord = service.getRandomDictionaryWord();

    ASSERT_EQ(*actualRandomizedDictionaryWord, dictionaryWord2);
}

TEST_F(DefaultDictionaryServiceTest, shouldAddDictionaryByName)
{
    EXPECT_CALL(*dictionaryRepository, addDictionary(dictionaryName1));

    service.addDictionary(dictionaryName1);
}

TEST_F(DefaultDictionaryServiceTest, givenNoneDictionaryWordsFromFile_shouldNotAddDictionary)
{
    EXPECT_CALL(*reader, readDictionaryWords(absoluteDictionaryWordsPath)).WillOnce(Return(boost::none));

    service.addDictionaryFromFile(dictionaryName1, absoluteDictionaryWordsPath);
}

TEST_F(DefaultDictionaryServiceTest, givenDictionaryWordsFromFile_shouldAddDictionary)
{
    EXPECT_CALL(*reader, readDictionaryWords(absoluteDictionaryWordsPath)).WillOnce(Return(dictionaryWords2));
    EXPECT_CALL(*dictionaryRepository, addDictionary(dictionary2));
    EXPECT_CALL(*dictionaryWordsRetriever, retrieveEnglishWords(dictionaryName2))
        .WillOnce(Return(englishWords));
    EXPECT_CALL(*observerService, notifyObservers(englishWords));

    service.addDictionaryFromFile(dictionaryName2, absoluteDictionaryWordsPath);
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
    EXPECT_CALL(*dictionaryRepository,
                removeWordFromDictionary(dictionaryWord1.englishWord, dictionaryName1));

    service.removeWordFromDictionary(dictionaryWord1.englishWord, dictionaryName1);
}

TEST_F(DefaultDictionaryServiceTest, shouldUpdateWordTranslationFromDictionary)
{
    EXPECT_CALL(*dictionaryRepository,
                changeWordTranslationFromDictionary(dictionaryWord1.englishWord, newDictionaryWordTranslation,
                                                    dictionaryName1));

    service.updateWordTranslationFromDictionary(dictionaryWord1.englishWord, newDictionaryWordTranslation,
                                                dictionaryName1);
}

TEST_F(DefaultDictionaryServiceTest,
       synchronizeDictionaries_shouldNotifyObserversAboutAllDictionaryEnglishWords)
{
    EXPECT_CALL(*dictionaryWordsRetriever, retrieveEnglishWords()).WillOnce(Return(englishWords));
    EXPECT_CALL(*observerService, notifyObservers(englishWords));

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
