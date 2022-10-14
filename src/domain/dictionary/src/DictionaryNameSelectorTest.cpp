#include "DictionaryNameSelector.h"

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
const Dictionary dictionary1{dictionaryName1, dictionaryWords1};
const Dictionary dictionary2{dictionaryName2, dictionaryWords2};
const std::vector<Dictionary> dictionaries{dictionary1, dictionary2};
const std::vector<Dictionary> emptyDictionaries{};
const std::vector<std::string> dictionaryNames{dictionaryName1, dictionaryName2};
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