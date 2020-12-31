#include "DictionaryFinder.h"

#include "gtest/gtest.h"
#include <boost/optional/optional_io.hpp>

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
const Dictionaries dictionaries1{dictionary1};
const Dictionaries dictionaries2{dictionary1, dictionary2};
const Dictionaries emptyDictionaries{};
const DictionaryNames dictionaryNames{dictionaryName1, dictionaryName2};
}

class DictionaryFinderTest : public Test
{
public:
    DictionaryFinder finder;
};

TEST_F(DictionaryFinderTest, givenEmptyDictionaries_shouldReturnNone)
{
    const auto actualDictionary = finder.findDictionary(dictionaryName1, emptyDictionaries);

    ASSERT_EQ(actualDictionary, boost::none);
}

TEST_F(DictionaryFinderTest, givenDictionaryNonExistingInDictionaries_shouldReturnNone)
{
    const auto actualDictionary = finder.findDictionary(dictionaryName2, dictionaries1);

    ASSERT_EQ(actualDictionary, boost::none);
}

TEST_F(DictionaryFinderTest, givenDictionaryExistingInDictionaries_shouldReturnDictionary)
{
    const auto actualDictionary = finder.findDictionary(dictionaryName2, dictionaries2);

    ASSERT_EQ(*actualDictionary, dictionary2);
}
