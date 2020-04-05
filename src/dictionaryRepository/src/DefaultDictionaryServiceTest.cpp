#include "DefaultDictionaryService.h"

#include "gtest/gtest.h"

#include "DictionaryNamesRetrieverMock.h"
#include "DictionaryWordRandomizerMock.h"
#include "DictionaryWordsRetrieverMock.h"
#include "RandomDictionaryWordRetrieverMock.h"
#include "dictionaryRepository/src/repository/DictionaryRepositoryMock.h"

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
const Dictionaries emptyDictionaries{};
const DictionaryNames dictionaryNames{dictionaryName1, dictionaryName2, dictionaryName3};
}

class DefaultDictionaryServiceTest : public Test
{
public:
    std::shared_ptr<DictionaryRepositoryMock> dictionaryRepository =
        std::make_shared<StrictMock<DictionaryRepositoryMock>>();

    std::unique_ptr<DictionaryNamesRetrieverMock> namesRetrieverInit =
        std::make_unique<StrictMock<DictionaryNamesRetrieverMock>>();
    DictionaryNamesRetrieverMock* dictionaryNamesRetriever = namesRetrieverInit.get();

    std::unique_ptr<DictionaryWordsRetrieverMock> wordsRetrieverInit =
        std::make_unique<StrictMock<DictionaryWordsRetrieverMock>>();
    DictionaryWordsRetrieverMock* dictionaryWordsRetriever = wordsRetrieverInit.get();

    std::unique_ptr<RandomDictionaryWordRetrieverMock> randomWordRetrieverInit =
        std::make_unique<StrictMock<RandomDictionaryWordRetrieverMock>>();
    RandomDictionaryWordRetrieverMock* randomDictionaryWordRetriever = randomWordRetrieverInit.get();

    DefaultDictionaryService service{dictionaryRepository, std::move(namesRetrieverInit),
                                     std::move(wordsRetrieverInit), std::move(randomWordRetrieverInit)};
};

TEST_F(DefaultDictionaryServiceTest, shouldReturnDictionaryNames)
{
    EXPECT_CALL(*dictionaryNamesRetriever, retrieveDictionaryNames()).WillOnce(Return(dictionaryNames));

    const auto actualDictionaryNames = service.getDictionaryNames();

    ASSERT_EQ(actualDictionaryNames, dictionaryNames);
}

TEST_F(DefaultDictionaryServiceTest, shouldReturnDictionaryWords)
{
    EXPECT_CALL(*dictionaryWordsRetriever, retrieveDictionaryWords(dictionaryName1)).WillOnce(Return(dictionaryWords1));

    const auto actualDictionaryWords = service.getDictionaryWords(dictionaryName1);

    ASSERT_EQ(actualDictionaryWords, dictionaryWords1);
}

TEST_F(DefaultDictionaryServiceTest, givenDictionaryName_shouldReturnRandomDictionaryWordFromThisDictionary)
{
    EXPECT_CALL(*randomDictionaryWordRetriever, getRandomDictionaryWord(dictionaryName1)).WillOnce(Return(dictionaryWord1));

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

TEST_F(DefaultDictionaryServiceTest, shouldAddDictionaryFromFile)
{
    EXPECT_CALL(*dictionaryRepository, addDictionaryFromFile(dictionaryName1, absoluteDictionaryWordsPath));

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
    EXPECT_CALL(*dictionaryRepository,
                removeWordFromDictionary(dictionaryWord1.englishWord, dictionaryName1));

    service.removeWordFromDictionary(dictionaryWord1.englishWord, dictionaryName1);
}
