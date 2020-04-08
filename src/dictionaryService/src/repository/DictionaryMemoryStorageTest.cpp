#include "DictionaryMemoryStorage.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace glossary::dictionaryService;
using namespace repository;

namespace
{
const DictionaryName dictionaryName1{"dictionaryName1"};
const DictionaryName dictionaryName2{"dictionaryName2"};
const DictionaryName dictionaryName3{"dictionaryName3"};
const DictionaryName dictionaryName4{"dictionaryName4"};
const DictionaryWord dictionaryWord1{"englishWord1", std::string{"translation1"}};
const DictionaryWord dictionaryWord2{"englishWord2", std::string{"translation2"}};
const DictionaryWord dictionaryWord3{"englishWord3", boost::none};
const Dictionary dictionary1{dictionaryName1,
                             DictionaryWords{dictionaryWord1, dictionaryWord2, dictionaryWord3}};
const Dictionary dictionary2{dictionaryName2, DictionaryWords{dictionaryWord1, dictionaryWord2}};
const Dictionaries dictionaries{dictionary1, dictionary2};
const Dictionary emptyDictionary1{dictionaryName1, {}};
const Dictionary emptyDictionary2{dictionaryName2, {}};
const Dictionary emptyDictionary3{dictionaryName3, {}};
const Dictionaries emptyDictionaries{emptyDictionary1, emptyDictionary2};
}

class DictionaryMemoryStorageTest : public Test
{
public:
    DictionaryMemoryStorage storage;
};

TEST_F(DictionaryMemoryStorageTest, givenDictionaryAdditionByName_shouldAddEmptyDictionary)
{
    storage.addDictionary(dictionaryName1);

    const auto actualDictionary = storage.getDictionary(dictionaryName1);

    ASSERT_TRUE(actualDictionary->words.empty());
}

TEST_F(DictionaryMemoryStorageTest, addTwoDifferentDictionariesByName_shouldAddTwoEmptyDictionaries)
{
    storage.addDictionary(dictionaryName1);
    storage.addDictionary(dictionaryName2);

    const auto actualDictionaries = storage.getDictionaries();

    ASSERT_EQ(actualDictionaries, emptyDictionaries);
}

TEST_F(DictionaryMemoryStorageTest, addTwoSameDictionariesByName_shouldAddOnlyOne)
{
    storage.addDictionary(dictionaryName1);
    storage.addDictionary(dictionaryName1);

    ASSERT_EQ(storage.size(), 1);
}

TEST_F(DictionaryMemoryStorageTest, givenDictionaryAddition_shouldAddDictionary)
{
    storage.addDictionary(dictionary1);

    const auto actualDictionary = storage.getDictionary(dictionaryName1);

    ASSERT_EQ(actualDictionary, dictionary1);
}

TEST_F(DictionaryMemoryStorageTest, addTwoDifferentDictionaries_shouldAddTwoDictionaries)
{
    storage.addDictionary(dictionary1);
    storage.addDictionary(dictionary2);

    const auto actualDictionaries = storage.getDictionaries();

    ASSERT_EQ(actualDictionaries, dictionaries);
}

TEST_F(DictionaryMemoryStorageTest, addTwoSameDictionaries_shouldAddOnlyOne)
{
    storage.addDictionary(dictionary1);
    storage.addDictionary(dictionary1);

    ASSERT_EQ(storage.size(), 1);
}

TEST_F(DictionaryMemoryStorageTest, givenNonExistingDictionary_shouldNotAddWordToDictionary)
{
    storage.addWordToDictionary(dictionaryWord1, dictionaryName1);

    const auto actualDictionary = storage.getDictionary(dictionaryName1);
    ASSERT_EQ(actualDictionary, boost::none);
}

TEST_F(DictionaryMemoryStorageTest, givenExistingDictionary_shouldAddWordToDictionary)
{
    storage.addDictionary(dictionaryName1);

    storage.addWordToDictionary(dictionaryWord1, dictionaryName1);

    const auto actualDictionary = storage.getDictionary(dictionaryName1);
    ASSERT_EQ(actualDictionary->words, DictionaryWords{dictionaryWord1});
}

TEST_F(DictionaryMemoryStorageTest,
       givenExistingDictionaryWithExactWord_shouldNotAddSecondSameWordToDictionary)
{
    storage.addDictionary(dictionaryName1);
    storage.addWordToDictionary(dictionaryWord1, dictionaryName1);

    storage.addWordToDictionary(dictionaryWord1, dictionaryName1);

    const auto actualDictionary = storage.getDictionary(dictionaryName1);
    ASSERT_EQ(actualDictionary->words, DictionaryWords{dictionaryWord1});
}

TEST_F(DictionaryMemoryStorageTest, shouldRemoveDictionary)
{
    storage.addDictionary(dictionary1);

    storage.removeDictionary(dictionaryName1);

    ASSERT_EQ(storage.size(), 0);
}

TEST_F(DictionaryMemoryStorageTest, givenTwoDictionaries_shouldRemoveOneDictionary)
{
    storage.addDictionary(dictionary1);
    storage.addDictionary(dictionary2);

    storage.removeDictionary(dictionaryName2);

    ASSERT_EQ(storage.size(), 1);
}

TEST_F(DictionaryMemoryStorageTest, givenEmptyStorage_getShouldNotReturnDictionary)
{
    const auto actualDictionary = storage.getDictionary(dictionaryName1);

    ASSERT_EQ(actualDictionary, boost::none);
}

TEST_F(DictionaryMemoryStorageTest, givenNonExistingDictionary_shouldNotRemoveWordFromDictionary)
{
    storage.removeWordFromDictionary(dictionaryWord1.englishWord, dictionaryName1);

    const auto actualDictionary = storage.getDictionary(dictionaryName1);
    ASSERT_EQ(actualDictionary, boost::none);
}

TEST_F(DictionaryMemoryStorageTest, givenExistingDictionary_shouldRemoveWordFromDictionary)
{
    storage.addDictionary(dictionaryName2);
    storage.addWordToDictionary(dictionaryWord2, dictionaryName2);

    storage.removeWordFromDictionary(dictionaryWord2.englishWord, dictionaryName2);

    const auto actualDictionary = storage.getDictionary(dictionaryName2);
    ASSERT_TRUE(actualDictionary->words.empty());
}

TEST_F(DictionaryMemoryStorageTest, givenDictionaryWithTwoWords_shouldRemoveOne)
{
    storage.addDictionary(dictionaryName2);
    storage.addWordToDictionary(dictionaryWord1, dictionaryName2);
    storage.addWordToDictionary(dictionaryWord2, dictionaryName2);

    storage.removeWordFromDictionary(dictionaryWord1.englishWord, dictionaryName2);

    const auto actualDictionary = storage.getDictionary(dictionaryName2);
    ASSERT_EQ(actualDictionary->words, DictionaryWords{dictionaryWord2});
}

TEST_F(DictionaryMemoryStorageTest, givenStorageWithExactDictionary_shouldReturnDictionary)
{
    storage.addDictionary(dictionaryName3);

    const auto actualDictionary = storage.getDictionary(dictionaryName3);

    ASSERT_EQ(actualDictionary, emptyDictionary3);
}

TEST_F(DictionaryMemoryStorageTest, givenEmptyStorage_shouldBeEmpty)
{
    ASSERT_TRUE(storage.empty());
}

TEST_F(DictionaryMemoryStorageTest, dictionaryNotExistingInStorage_getShouldNotContainThisDictionary)
{
    ASSERT_FALSE(storage.containsDictionary(dictionaryName4));
}

TEST_F(DictionaryMemoryStorageTest, givenWordExistingInStorage_getShouldContainThisWord)
{
    storage.addDictionary(dictionaryName3);

    const auto containsDictionary = storage.containsDictionary(dictionaryName3);

    ASSERT_TRUE(containsDictionary);
}
