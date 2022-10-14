#include "DefaultDictionaryWordsRetriever.h"

#include "gtest/gtest.h"

#include "repository/DictionaryRepositoryMock.h"

using namespace ::testing;
using namespace glossary::dictionary;

namespace
{
const std::string dictionaryName1{"dictionaryName1"};
const std::string dictionaryName2{"dictionaryName2"};
const std::string dictionaryName3{"dictionaryName3"};
const std::string nonExistingDictionaryName{"nonExisting"};
const DictionaryWord dictionaryWord1{"englishWord1", std::string{"translation1"}};
const DictionaryWord dictionaryWord2{"englishWord2", std::string{"translation2"}};
const DictionaryWord dictionaryWord3{"englishWord3", std::nullopt};
const std::vector<DictionaryWord> dictionaryWords1{dictionaryWord1, dictionaryWord2, dictionaryWord3};
const std::vector<DictionaryWord> dictionaryWords2{dictionaryWord1, dictionaryWord2};
const std::vector<DictionaryWord> dictionaryWordsSum{dictionaryWord1, dictionaryWord2, dictionaryWord3,
                                                     dictionaryWord1, dictionaryWord2};
const std::vector<DictionaryWord> emptyDictionaryWords{};
const Dictionary dictionary1{dictionaryName1, dictionaryWords1};
const Dictionary dictionary2{dictionaryName2, dictionaryWords2};
const Dictionary emptyDictionary{dictionaryName3, emptyDictionaryWords};
const std::vector<Dictionary> dictionaries{dictionary1, dictionary2, emptyDictionary};
const std::vector<std::string> englishWords{dictionaryWord1.englishWord, dictionaryWord2.englishWord,
                                            dictionaryWord3.englishWord};
const std::vector<std::string> accumulatedEnglishWords{
    dictionaryWord1.englishWord, dictionaryWord2.englishWord, dictionaryWord3.englishWord,
    dictionaryWord1.englishWord, dictionaryWord2.englishWord};
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

    ASSERT_EQ(actualDictionaryWords, std::nullopt);
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

    ASSERT_EQ(actualEnglishWords, std::nullopt);
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