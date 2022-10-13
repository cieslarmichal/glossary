#include "WordsDictionaryMembershipFinder.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace glossary::dictionaryService;

namespace
{
const DictionaryName dictionaryName1{"dictionaryName1"};
const DictionaryName dictionaryName2{"dictionaryName2"};
const DictionaryNames dictionaryNames1{dictionaryName1};
const DictionaryNames dictionaryNames2{dictionaryName1, dictionaryName2};
const std::string englishWord1{"englishWord1"};
const std::string englishWord2{"englishWord2"};
const std::string englishWord3{"englishWord3"};
const std::string englishWord4{"englishWord4"};
const std::string englishWordTranslation1{"translation1"};
const std::string englishWordTranslation2{"translation2"};
const std::string englishWordTranslation3{"translation3"};
const DictionaryWord dictionaryWord1{englishWord1, englishWordTranslation1};
const DictionaryWord dictionaryWord2{englishWord2, englishWordTranslation2};
const DictionaryWord dictionaryWord3{englishWord3, boost::none};
const DictionaryWord dictionaryWord4{englishWord4, boost::none};
const DictionaryWords dictionaryWords1{dictionaryWord1, dictionaryWord2, dictionaryWord3};
const DictionaryWords dictionaryWords2{dictionaryWord1, dictionaryWord2};
const Dictionary dictionary1{dictionaryName1, dictionaryWords1};
const Dictionary dictionary2{dictionaryName2, dictionaryWords2};
const Dictionaries emptyDictionaries{};
const Dictionaries dictionaries1{dictionary1};
const Dictionaries dictionaries2{dictionary1, dictionary2};
}

class WordsDictionaryMembershipFinderTest : public Test
{
public:
    WordsDictionaryMembershipFinder finder;
};

TEST_F(WordsDictionaryMembershipFinderTest,
       givenEmptyDictionaries_shouldReturnEmptyDictionaryNamesContainingEnglishWords)
{
    const auto actualDictionaryNames =
        finder.findDictionariesContainingEnglishWord(englishWord1, emptyDictionaries);

    ASSERT_TRUE(actualDictionaryNames.empty());
}

TEST_F(WordsDictionaryMembershipFinderTest,
       givenEnglishWordNotOccuringInAnyDictionary_shouldReturnEmptyDictionaryNames)
{
    const auto actualDictionaryNames =
        finder.findDictionariesContainingEnglishWord(englishWord4, dictionaries2);

    ASSERT_TRUE(actualDictionaryNames.empty());
}

TEST_F(WordsDictionaryMembershipFinderTest, givenEnglishWordOccuringInDictionary_shouldReturnDictionaryName)
{
    const auto actualDictionaryNames =
        finder.findDictionariesContainingEnglishWord(englishWord1, dictionaries1);

    ASSERT_EQ(actualDictionaryNames, dictionaryNames1);
}

TEST_F(WordsDictionaryMembershipFinderTest,
       givenEnglishWordOccuringInTwoDictionaries_shouldReturnDictionariesNames)
{
    const auto actualDictionaryNames =
        finder.findDictionariesContainingEnglishWord(englishWord1, dictionaries2);

    ASSERT_EQ(actualDictionaryNames, dictionaryNames2);
}

TEST_F(WordsDictionaryMembershipFinderTest,
       givenEmptyDictionaries_shouldReturnEmptyDictionaryNamesContainingEnglishWordsTranslations)
{
    const auto actualDictionaryNames =
        finder.findDictionariesContainingEnglishWordTranslation(englishWordTranslation1, emptyDictionaries);

    ASSERT_TRUE(actualDictionaryNames.empty());
}

TEST_F(WordsDictionaryMembershipFinderTest,
       givenEnglishWordTranslationNotOccuringInAnyDictionary_shouldReturnEmptyDictionaryNames)
{
    const auto actualDictionaryNames =
        finder.findDictionariesContainingEnglishWordTranslation(englishWordTranslation3, dictionaries2);

    ASSERT_TRUE(actualDictionaryNames.empty());
}

TEST_F(WordsDictionaryMembershipFinderTest,
       givenEnglishWordTranslationOccuringInDictionary_shouldReturnDictionaryName)
{
    const auto actualDictionaryNames =
        finder.findDictionariesContainingEnglishWordTranslation(englishWordTranslation2, dictionaries1);

    ASSERT_EQ(actualDictionaryNames, dictionaryNames1);
}

TEST_F(WordsDictionaryMembershipFinderTest,
       givenEnglishWordTranslationOccuringInTwoDictionaries_shouldReturnDictionariesNames)
{
    const auto actualDictionaryNames =
        finder.findDictionariesContainingEnglishWordTranslation(englishWordTranslation2, dictionaries2);

    ASSERT_EQ(actualDictionaryNames, dictionaryNames2);
}