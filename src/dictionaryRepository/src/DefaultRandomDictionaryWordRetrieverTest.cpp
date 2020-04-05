#include "DefaultRandomDictionaryWordRetriever.h"

#include "gtest/gtest.h"

#include "DictionaryWordRandomizerMock.h"
#include "dictionaryRepository/src/repository/DictionaryRepositoryMock.h"

using namespace ::testing;
using namespace glossary::dictionaryService;

namespace
{
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
}

class DefaultRandomDictionaryWordRetrieverTest : public Test
{
public:
    std::shared_ptr<DictionaryRepositoryMock> dictionaryRepository =
        std::make_shared<StrictMock<DictionaryRepositoryMock>>();
    std::unique_ptr<DictionaryWordRandomizerMock> randomizerInit =
        std::make_unique<StrictMock<DictionaryWordRandomizerMock>>();
    DictionaryWordRandomizerMock* randomizer = randomizerInit.get();
    DefaultRandomDictionaryWordRetriever retriever{dictionaryRepository, std::move(randomizerInit)};
};

TEST_F(DefaultRandomDictionaryWordRetrieverTest,
       givenNonExistingDictionary_shouldReturnNoneRandomDictionaryWord)
{
    EXPECT_CALL(*dictionaryRepository, getDictionaries()).WillOnce(Return(dictionaries));

    const auto actualRandomizedDictionaryWord = retriever.getRandomDictionaryWord(nonExistingDictionaryName);

    ASSERT_EQ(actualRandomizedDictionaryWord, boost::none);
}

TEST_F(DefaultRandomDictionaryWordRetrieverTest,
       givenEmptyDictionaryWordsInDictionary_shouldReturnNoneRandomDictionaryWord)
{
    EXPECT_CALL(*dictionaryRepository, getDictionaries()).WillOnce(Return(dictionaries));
    EXPECT_CALL(*randomizer, randomize(emptyDictionaryWords))
        .WillOnce(Throw(std::invalid_argument{"empty words"}));

    const auto actualRandomizedDictionaryWord = retriever.getRandomDictionaryWord(dictionaryName3);

    ASSERT_EQ(actualRandomizedDictionaryWord, boost::none);
}

TEST_F(DefaultRandomDictionaryWordRetrieverTest,
       givenDictionaryWordsInDictionary_shouldReturnRandomDictionaryWordFromThisDictionary)
{
    EXPECT_CALL(*dictionaryRepository, getDictionaries()).WillOnce(Return(dictionaries));
    EXPECT_CALL(*randomizer, randomize(dictionaryWords1)).WillOnce(Return(dictionaryWord1));

    const auto actualRandomizedDictionaryWord = retriever.getRandomDictionaryWord(dictionaryName1);

    ASSERT_EQ(*actualRandomizedDictionaryWord, dictionaryWord1);
}

TEST_F(DefaultRandomDictionaryWordRetrieverTest, givenEmptyDictionaryWordsInDictionaries_shouldReturnNone)
{
    EXPECT_CALL(*dictionaryRepository, getDictionaries()).WillOnce(Return(emptyDictionaries));
    EXPECT_CALL(*randomizer, randomize(emptyDictionaryWords))
        .WillOnce(Throw(std::invalid_argument{"empty words"}));

    const auto actualRandomizedDictionaryWord = retriever.getRandomDictionaryWord();

    ASSERT_EQ(actualRandomizedDictionaryWord, boost::none);
}

TEST_F(DefaultRandomDictionaryWordRetrieverTest,
       givenDictionaryWordsInDictionaries_shouldReturnRandomDictionaryWord)
{
    EXPECT_CALL(*dictionaryRepository, getDictionaries()).WillOnce(Return(dictionaries));
    EXPECT_CALL(*randomizer, randomize(dictionaryWordsSum)).WillOnce(Return(dictionaryWord2));

    const auto actualRandomizedDictionaryWord = retriever.getRandomDictionaryWord();

    ASSERT_EQ(*actualRandomizedDictionaryWord, dictionaryWord2);
}