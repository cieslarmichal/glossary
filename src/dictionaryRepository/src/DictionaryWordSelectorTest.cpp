#include "DictionaryWordSelector.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace glossary::dictionaryService;

namespace
{
const DictionaryName dictionaryName1{"dictionaryName1"};
const DictionaryName dictionaryName2{"dictionaryName2"};
const DictionaryWord dictionaryWord1{"englishWord1", std::string{"translation1"}};
const DictionaryWord dictionaryWord2{"englishWord2", std::string{"translation2"}};
const DictionaryWord dictionaryWord3{"englishWord3", boost::none};
const DictionaryWords dictionaryWords1{dictionaryWord1, dictionaryWord2, dictionaryWord3};
const DictionaryWords dictionaryWords2{dictionaryWord1, dictionaryWord2};
const DictionaryWords dictionaryWordsSum{dictionaryWord1, dictionaryWord2, dictionaryWord3, dictionaryWord1,
                                         dictionaryWord2};
const Dictionary dictionary1{dictionaryName1, dictionaryWords1};
const Dictionary dictionary2{dictionaryName2, dictionaryWords2};
const Dictionaries dictionaries{dictionary1, dictionary2};
}

class DictionaryWordSelectorTest : public Test
{
public:
    DictionaryWordSelector selector;
};

TEST_F(DictionaryWordSelectorTest, shouldReturnDictionaryWordsFromDictionary)
{
    const auto actualDictionaryWords = selector.selectWords(dictionary1);

    ASSERT_EQ(actualDictionaryWords, dictionaryWords1);
}

TEST_F(DictionaryWordSelectorTest, shouldReturnDictionaryWordsFromDictionaries)
{
    const auto actualDictionaryWords = selector.selectWords(dictionaries);

    ASSERT_EQ(actualDictionaryWords, dictionaryWordsSum);
}