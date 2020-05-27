#include "FormattedDictionariesStorage.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace glossary::gui::view;

class FormattedDictionariesStorageTest : public Test
{
public:
    const FormattedDictionaryWord formattedDictionaryWord1{"englishWord1", "translation1"};
    const FormattedDictionaryWord formattedDictionaryWord2{"englishWord2", "translation2"};
    const FormattedDictionaryWord formattedDictionaryWord3{"englishWord3", ""};
    const FormattedDictionaryWords formattedDictionaryWords{
        formattedDictionaryWord1, formattedDictionaryWord2, formattedDictionaryWord3};
    const FormattedDictionaryWords formattedDictionaryWordsAfterUpdate{formattedDictionaryWord1,
                                                                       formattedDictionaryWord3};
    const FormattedDictionaryWords emptyFormattedDictionaryWords{};
    const QString dictionaryName1{"dictionaryName1"};
    const QString dictionaryName2{"dictionaryName2"};
    const QStringList dictionaryNames{dictionaryName1, dictionaryName2};
    const FormattedDictionary formattedDictionary1{dictionaryName1, formattedDictionaryWords};
    const FormattedDictionary formattedDictionary1AfterUpdate{dictionaryName1,
                                                              formattedDictionaryWordsAfterUpdate};
    const FormattedDictionary formattedDictionary2{dictionaryName2, emptyFormattedDictionaryWords};
    const QList<FormattedDictionary> dictionaries1{formattedDictionary1};
    const QList<FormattedDictionary> dictionariesAfterUpdate{formattedDictionary1AfterUpdate};
    const QList<FormattedDictionary> dictionaries2{formattedDictionary1, formattedDictionary2};
    const QList<FormattedDictionary> emptyDictionaries{};
};

TEST_F(FormattedDictionariesStorageTest, givenEmptyDictionaries_shouldReturnEmptyDictionaries)
{
    FormattedDictionariesStorage dictionariesStorage{emptyDictionaries};

    const auto actualDictionaries = dictionariesStorage.getDictionaries();

    ASSERT_TRUE(actualDictionaries.empty());
}

TEST_F(FormattedDictionariesStorageTest, givenNonEmptyDictionaries_shouldReturnDictionaries)
{
    FormattedDictionariesStorage dictionariesStorage{dictionaries1};

    const auto actualDictionaries = dictionariesStorage.getDictionaries();

    ASSERT_EQ(actualDictionaries, dictionaries1);
}

TEST_F(FormattedDictionariesStorageTest,
       givenDictionaryNameNonExistingInDictionaries_shouldNotUpdateDictionaryWords)
{
    FormattedDictionariesStorage dictionariesStorage{dictionaries1};

    dictionariesStorage.updateDictionaryWords(dictionaryName2, formattedDictionaryWords);

    const auto actualDictionaries = dictionariesStorage.getDictionaries();
    ASSERT_EQ(actualDictionaries, dictionaries1);
}

TEST_F(FormattedDictionariesStorageTest,
       givenDictionaryNameExistingInDictionaries_shouldUpdateDictionaryWords)
{
    FormattedDictionariesStorage dictionariesStorage{dictionaries1};

    dictionariesStorage.updateDictionaryWords(dictionaryName1, formattedDictionaryWordsAfterUpdate);

    const auto actualDictionaries = dictionariesStorage.getDictionaries();
    ASSERT_EQ(actualDictionaries, dictionariesAfterUpdate);
}

TEST_F(FormattedDictionariesStorageTest, shouldUpdateDictionaries)
{
    FormattedDictionariesStorage dictionariesStorage{dictionaries1};

    dictionariesStorage.updateDictionaries(dictionaries2);

    const auto actualDictionaries = dictionariesStorage.getDictionaries();
    ASSERT_EQ(actualDictionaries, dictionaries2);
}

TEST_F(FormattedDictionariesStorageTest, shouldReturnDictionaryNames)
{
    FormattedDictionariesStorage dictionariesStorage{dictionaries2};

    const auto actualDictionaryNames = dictionariesStorage.getDictionaryNames();

    ASSERT_EQ(actualDictionaryNames, dictionaryNames);
}

TEST_F(FormattedDictionariesStorageTest, givenNonExistingDictionaryName_shouldReturnEmptyDictionaryWords)
{
    FormattedDictionariesStorage dictionariesStorage{dictionaries1};

    const auto actualDictionaryWords = dictionariesStorage.getDictionaryWords(dictionaryName2);

    ASSERT_TRUE(actualDictionaryWords.empty());
}

TEST_F(FormattedDictionariesStorageTest, givenExistingDictionaryName_shouldReturnDictionaryWords)
{
    FormattedDictionariesStorage dictionariesStorage{dictionaries1};

    const auto actualDictionaryWords = dictionariesStorage.getDictionaryWords(dictionaryName1);

    ASSERT_EQ(actualDictionaryWords, formattedDictionaryWords);
}

TEST_F(FormattedDictionariesStorageTest, givenEmptyDictionaries_shouldReturnTrue)
{
    FormattedDictionariesStorage dictionariesStorage{emptyDictionaries};

    const auto actualDictionariesEmpty = dictionariesStorage.dictionariesAreEmpty();

    ASSERT_TRUE(actualDictionariesEmpty);
}

TEST_F(FormattedDictionariesStorageTest, givenNonEmptyDictionaries_shouldReturnFalse)
{
    FormattedDictionariesStorage dictionariesStorage{dictionaries1};

    const auto actualDictionariesEmpty = dictionariesStorage.dictionariesAreEmpty();

    ASSERT_FALSE(actualDictionariesEmpty);
}
