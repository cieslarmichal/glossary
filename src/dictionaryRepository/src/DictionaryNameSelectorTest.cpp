#include "DictionaryNameSelector.h"

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
const Dictionary dictionary1{dictionaryName1, dictionaryWords1};
const Dictionary dictionary2{dictionaryName2, dictionaryWords2};
const Dictionaries dictionaries{dictionary1, dictionary2};
const Dictionaries emptyDictionaries{};
const DictionaryNames dictionaryNames{dictionaryName1, dictionaryName2};
}

class DictionaryNameSelectorTest : public Test
{
public:
    DictionaryNameSelector selector;
};

TEST_F(DictionaryNameSelectorTest, givenEmptyDictionaries_shouldReturnEmptyDictionaryNames)
{
    const auto actualDictionaryNames = selector.selectNames(emptyDictionaries);

    ASSERT_TRUE(actualDictionaryNames.empty());
}

TEST_F(DictionaryNameSelectorTest, givenDictionaries_shouldReturnDictionaryNames)
{
    const auto actualDictionaryNames = selector.selectNames(dictionaries);

    ASSERT_EQ(actualDictionaryNames, dictionaryNames);
}