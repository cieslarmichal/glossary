#include "DictionaryFinder.h"

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
const std::vector<Dictionary> dictionaries1{dictionary1};
const std::vector<Dictionary> dictionaries2{dictionary1, dictionary2};
const std::vector<Dictionary> emptyDictionaries{};
const std::vector<std::string> dictionaryNames{dictionaryName1, dictionaryName2};
}

class DictionaryFinderTest : public Test
{
public:
    DictionaryFinder finder;
};

TEST_F(DictionaryFinderTest, givenEmptyDictionaries_shouldReturnNone)
{
    const auto actualDictionary = finder.findDictionary(dictionaryName1, emptyDictionaries);

    ASSERT_EQ(actualDictionary, std::nullopt);
}

TEST_F(DictionaryFinderTest, givenDictionaryNonExistingInDictionaries_shouldReturnNone)
{
    const auto actualDictionary = finder.findDictionary(dictionaryName2, dictionaries1);

    ASSERT_EQ(actualDictionary, std::nullopt);
}

TEST_F(DictionaryFinderTest, givenDictionaryExistingInDictionaries_shouldReturnDictionary)
{
    const auto actualDictionary = finder.findDictionary(dictionaryName2, dictionaries2);

    ASSERT_EQ(*actualDictionary, dictionary2);
}
