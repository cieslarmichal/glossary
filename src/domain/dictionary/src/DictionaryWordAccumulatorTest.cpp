#include "DictionaryWordAccumulator.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace glossary::dictionary;

namespace
{
const std::string dictionaryName1{"dictionaryName1"};
const std::string dictionaryName2{"dictionaryName2"};
const DictionaryWord dictionaryWord1{"englishWord1", std::string{"translation1"}};
const DictionaryWord dictionaryWord2{"englishWord2", std::string{"translation2"}};
const DictionaryWord dictionaryWord3{"englishWord3", std::nullopt};
const std::vector<DictionaryWord> dictionaryWords1{dictionaryWord1, dictionaryWord2, dictionaryWord3};
const std::vector<DictionaryWord> dictionaryWords2{dictionaryWord1, dictionaryWord2};
const std::vector<DictionaryWord> accumulatedDictionaryWords{
    dictionaryWord1, dictionaryWord2, dictionaryWord3, dictionaryWord1, dictionaryWord2};
const Dictionary dictionary1{dictionaryName1, dictionaryWords1};
const Dictionary dictionary2{dictionaryName2, dictionaryWords2};
const std::vector<Dictionary> dictionaries{dictionary1, dictionary2};
const std::vector<std::string> englishWords{dictionaryWord1.englishWord, dictionaryWord2.englishWord,
                                            dictionaryWord3.englishWord};
const std::vector<std::string> accumulatedEnglishWords{
    dictionaryWord1.englishWord, dictionaryWord2.englishWord, dictionaryWord3.englishWord,
    dictionaryWord1.englishWord, dictionaryWord2.englishWord};
}

class DictionaryWordAccumulatorTest : public Test
{
public:
    DictionaryWordAccumulator accumulator;
};

TEST_F(DictionaryWordAccumulatorTest, shouldReturnDictionaryWordsFromDictionary)
{
    const auto actualDictionaryWords = accumulator.accumulateDictionaryWords(dictionary1);

    ASSERT_EQ(actualDictionaryWords, dictionaryWords1);
}

TEST_F(DictionaryWordAccumulatorTest, shouldReturnDictionaryWordsFromDictionaries)
{
    const auto actualDictionaryWords = accumulator.accumulateDictionaryWords(dictionaries);

    ASSERT_EQ(actualDictionaryWords, accumulatedDictionaryWords);
}

TEST_F(DictionaryWordAccumulatorTest, shouldReturnEnglishWordsFromDictionary)
{
    const auto actualEnglishWords = accumulator.accumulateEnglishWords(dictionary1);

    ASSERT_EQ(actualEnglishWords, englishWords);
}

TEST_F(DictionaryWordAccumulatorTest, shouldReturnEnglishWordsFromDictionaries)
{
    const auto actualEnglishWords = accumulator.accumulateEnglishWords(dictionaries);

    ASSERT_EQ(actualEnglishWords, accumulatedEnglishWords);
}