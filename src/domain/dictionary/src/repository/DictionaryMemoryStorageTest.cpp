#include "DictionaryMemoryStorage.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace glossary::dictionary;

class DictionaryMemoryStorageTest : public Test
{
public:
    const std::string dictionaryName1{"dictionaryName1"};
    const std::string dictionaryName2{"dictionaryName2"};
    const std::string dictionaryName3{"dictionaryName3"};
    const std::string dictionaryName4{"dictionaryName4"};
    const DictionaryWord dictionaryWord1{"englishWord1", std::string{"translation1"}};
    const DictionaryWord dictionaryWord2{"englishWord2", std::string{"translation2"}};
    const DictionaryWord dictionaryWord3{"englishWord3", std::nullopt};
    const Dictionary dictionary1{dictionaryName1,
                                 std::vector<DictionaryWord>{dictionaryWord1, dictionaryWord2, dictionaryWord3}};
    const Dictionary dictionary2{dictionaryName2, std::vector<DictionaryWord>{dictionaryWord1, dictionaryWord2}};
    const std::vector<Dictionary> dictionaries{dictionary1, dictionary2};
    const Dictionary emptyDictionary1{dictionaryName1, {}};
    const Dictionary emptyDictionary2{dictionaryName2, {}};
    const Dictionary emptyDictionary3{dictionaryName3, {}};
    const std::vector<Dictionary> emptyDictionaries{emptyDictionary1, emptyDictionary2};
    const std::string newDictionaryWordTranslation{"newDictionaryWordTranslation"};

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

TEST_F(DictionaryMemoryStorageTest, shouldAddDictionary)
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
    ASSERT_EQ(actualDictionary, std::nullopt);
}

TEST_F(DictionaryMemoryStorageTest, givenExistingDictionary_shouldAddWordToDictionary)
{
    storage.addDictionary(dictionaryName1);

    storage.addWordToDictionary(dictionaryWord1, dictionaryName1);

    const auto actualDictionary = storage.getDictionary(dictionaryName1);
    ASSERT_EQ(actualDictionary->words, std::vector<DictionaryWord>{dictionaryWord1});
}

TEST_F(DictionaryMemoryStorageTest, givenExistingDictionaryWithExactWord_shouldNotAddSecondSameWordToDictionary)
{
    storage.addDictionary(dictionaryName1);
    storage.addWordToDictionary(dictionaryWord1, dictionaryName1);

    storage.addWordToDictionary(dictionaryWord1, dictionaryName1);

    const auto actualDictionary = storage.getDictionary(dictionaryName1);
    ASSERT_EQ(actualDictionary->words, std::vector<DictionaryWord>{dictionaryWord1});
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

TEST_F(DictionaryMemoryStorageTest, givenNonExistingDictionary_shouldNotRemoveWordFromDictionary)
{
    storage.removeWordFromDictionary(dictionaryWord1.englishWord, dictionaryName1);

    const auto actualDictionary = storage.getDictionary(dictionaryName1);
    ASSERT_EQ(actualDictionary, std::nullopt);
}

TEST_F(DictionaryMemoryStorageTest, givenExistingDictionaryWithExistingWord_shouldRemoveWordFromDictionary)
{
    storage.addDictionary(dictionaryName2);
    storage.addWordToDictionary(dictionaryWord2, dictionaryName2);

    storage.removeWordFromDictionary(dictionaryWord2.englishWord, dictionaryName2);

    const auto actualDictionary = storage.getDictionary(dictionaryName2);
    ASSERT_TRUE(actualDictionary->words.empty());
}

TEST_F(DictionaryMemoryStorageTest, givenNonExistingDictionary_shouldNotChangeWordTranslation)
{
    storage.changeWordTranslationFromDictionary(dictionaryWord1.englishWord, newDictionaryWordTranslation,
                                                dictionaryName1);

    const auto actualDictionary = storage.getDictionary(dictionaryName1);
    ASSERT_EQ(actualDictionary, std::nullopt);
}

TEST_F(DictionaryMemoryStorageTest, givenExistingDictionaryWithNonExistingWord_shouldNotChangeWordTranslation)
{
    storage.addDictionary(dictionaryName1);

    storage.changeWordTranslationFromDictionary(dictionaryWord1.englishWord, newDictionaryWordTranslation,
                                                dictionaryName1);

    const auto actualDictionary = storage.getDictionary(dictionaryName1);
    ASSERT_TRUE(actualDictionary->words.empty());
}

TEST_F(DictionaryMemoryStorageTest, givenExistingDictionaryWithExistingWord_shouldChangeWordTranslation)
{
    storage.addDictionary(dictionaryName1);
    storage.addWordToDictionary(dictionaryWord1, dictionaryName1);

    storage.changeWordTranslationFromDictionary(dictionaryWord1.englishWord, newDictionaryWordTranslation,
                                                dictionaryName1);

    const auto actualDictionary = storage.getDictionary(dictionaryName1);
    const auto words = actualDictionary->words;
    auto dictionaryWord = std::find_if(words.begin(), words.end(),
                                       [&](const DictionaryWord& dictionaryWord)
                                       { return dictionaryWord.englishWord == dictionaryWord1.englishWord; });
    ASSERT_TRUE(dictionaryWord != words.end());
    ASSERT_EQ(dictionaryWord->translation, newDictionaryWordTranslation);
}

TEST_F(DictionaryMemoryStorageTest, givenDictionaryWithTwoWords_shouldRemoveOne)
{
    storage.addDictionary(dictionaryName2);
    storage.addWordToDictionary(dictionaryWord1, dictionaryName2);
    storage.addWordToDictionary(dictionaryWord2, dictionaryName2);

    storage.removeWordFromDictionary(dictionaryWord1.englishWord, dictionaryName2);

    const auto actualDictionary = storage.getDictionary(dictionaryName2);
    ASSERT_EQ(actualDictionary->words, std::vector<DictionaryWord>{dictionaryWord2});
}

TEST_F(DictionaryMemoryStorageTest, givenEmptyStorage_getShouldNotReturnDictionary)
{
    const auto actualDictionary = storage.getDictionary(dictionaryName1);

    ASSERT_EQ(actualDictionary, std::nullopt);
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
