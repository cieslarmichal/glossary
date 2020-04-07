#include "DefaultDictionaryWordsRetriever.h"

#include "gtest/gtest.h"

#include "repository/DictionaryRepositoryMock.h"

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
const EnglishWords englishWords{dictionaryWord1.englishWord, dictionaryWord2.englishWord,
                                dictionaryWord3.englishWord};
const EnglishWords accumulatedEnglishWords{dictionaryWord1.englishWord, dictionaryWord2.englishWord,
                                           dictionaryWord3.englishWord, dictionaryWord1.englishWord,
                                           dictionaryWord2.englishWord};
}

class DefaultDictionaryWordsRetrieverTest : public Test
{
public:
    std::shared_ptr<repository::DictionaryRepositoryMock> dictionaryRepository =
        std::make_shared<StrictMock<repository::DictionaryRepositoryMock>>();
    DefaultDictionaryWordsRetriever retriever{dictionaryRepository};
};

TEST_F(DefaultDictionaryWordsRetrieverTest, givenNonExistingDictionary_shouldReturnEmptyDictionaryWords)
{
    EXPECT_CALL(*dictionaryRepository, getDictionaries()).WillOnce(Return(dictionaries));

    const auto actualDictionaryWords = retriever.retrieveDictionaryWords(nonExistingDictionaryName);

    ASSERT_EQ(actualDictionaryWords, boost::none);
}

TEST_F(DefaultDictionaryWordsRetrieverTest, givenExistingDictionary_shouldReturnDictionaryWords)
{
    EXPECT_CALL(*dictionaryRepository, getDictionaries()).WillOnce(Return(dictionaries));

    const auto actualDictionaryWords = retriever.retrieveDictionaryWords(dictionaryName1);

    ASSERT_EQ(*actualDictionaryWords, dictionaryWords1);
}

TEST_F(DefaultDictionaryWordsRetrieverTest, givenNonExistingDictionary_shouldReturnEmptyEnglishWords)
{
    EXPECT_CALL(*dictionaryRepository, getDictionaries()).WillOnce(Return(dictionaries));

    const auto actualEnglishWords = retriever.retrieveEnglishWords(nonExistingDictionaryName);

    ASSERT_EQ(actualEnglishWords, boost::none);
}

TEST_F(DefaultDictionaryWordsRetrieverTest, givenExistingDictionary_shouldReturnEnglishWords)
{
    EXPECT_CALL(*dictionaryRepository, getDictionaries()).WillOnce(Return(dictionaries));

    const auto actualEnglishWords = retriever.retrieveEnglishWords(dictionaryName1);

    ASSERT_EQ(*actualEnglishWords, englishWords);
}

TEST_F(DefaultDictionaryWordsRetrieverTest, givenDictionaries_shouldReturnEnglishWords)
{
    EXPECT_CALL(*dictionaryRepository, getDictionaries()).WillOnce(Return(dictionaries));

    const auto actualEnglishWords = retriever.retrieveEnglishWords();

    ASSERT_EQ(actualEnglishWords, accumulatedEnglishWords);
}