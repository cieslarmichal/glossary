#include "DictionaryPersistentStorage.h"

#include <boost/optional/optional_io.hpp>

#include "gtest/gtest.h"

#include "../../../common/fileSystem/include/FileAccessMock.h"
#include "serialization/DictionarySerializerMock.h"

#include "../../../common/fileSystem/include/GetProjectPath.h"

using namespace ::testing;
using namespace glossary::dictionaryService;
using namespace repository;

namespace
{
const std::string filePath{common::getProjectPath("glossary") + "repositoryFiles/dictionaries.txt"};
const std::string newDictionaryWordTranslation{"newDictionaryWordTranslation"};
const DictionaryName dictionaryName1{"dictionaryName1"};
const DictionaryName dictionaryName2{"dictionaryName2"};
const DictionaryName dictionaryName3{"dictionaryName3"};
const DictionaryName nonExistingDictionaryName{"nonExistingDict"};
const DictionaryWord dictionaryWord1{"englishWord1", std::string{"translation1"}};
const DictionaryWord dictionaryWord1AfterChange{"englishWord1", newDictionaryWordTranslation};
const DictionaryWord dictionaryWord2{"englishWord2", std::string{"translation2"}};
const DictionaryWord dictionaryWord3{"englishWord3", boost::none};
const DictionaryWord dictionaryWord4{"englishWord4", boost::none};
const DictionaryWords dictionaryWords1{dictionaryWord1, dictionaryWord2, dictionaryWord3};
const DictionaryWords dictionaryWords1AfterAddition{dictionaryWord1, dictionaryWord2, dictionaryWord3,
                                                    dictionaryWord4};
const DictionaryWords dictionaryWords1AfterTranslationChange{dictionaryWord1AfterChange, dictionaryWord2,
                                                             dictionaryWord3};
const DictionaryWords dictionaryWords1AfterRemoval{dictionaryWord2, dictionaryWord3};
const DictionaryWords dictionaryWords2{dictionaryWord1, dictionaryWord2};
const Dictionary dictionary1{dictionaryName1, dictionaryWords1};
const Dictionary dictionary1AfterAddition{dictionaryName1, dictionaryWords1AfterAddition};
const Dictionary dictionary1AfterRemoval{dictionaryName1, dictionaryWords1AfterRemoval};
const Dictionary dictionary1AfterTranslationChange{dictionaryName1, dictionaryWords1AfterTranslationChange};
const Dictionary dictionary2{dictionaryName2, dictionaryWords2};
const Dictionary emptyDictionary1{dictionaryName1, {}};
const Dictionary emptyDictionary2{dictionaryName2, {}};
const Dictionaries twoDictionaries{dictionary1, dictionary2};
const Dictionaries twoDictionariesAfterAddition{dictionary1AfterAddition, dictionary2};
const Dictionaries twoDictionariesAfterTranslationChange{dictionary1AfterTranslationChange, dictionary2};
const Dictionaries twoDictionariesAfterRemoval{dictionary1AfterRemoval, dictionary2};
const Dictionaries dictionariesAfterRemoval{dictionary2};
const Dictionaries dictionariesWithOneDictionary{dictionary1};
const Dictionaries dictionariesWithOneEmptyDictionary{emptyDictionary1};
const Dictionaries emptyDictionaries{emptyDictionary1, emptyDictionary2};
const Dictionaries noDictionaries{};
}

class DictionaryPersistentStorageTest : public Test
{
public:
    void expectNoDictionariesLoad()
    {
        EXPECT_CALL(*fileAccess, exists(filePath)).WillOnce(Return(true));
        EXPECT_CALL(*fileAccess, readContent(filePath)).WillOnce(Return("some content"));
        EXPECT_CALL(*serializer, deserialize("some content")).WillOnce(Return(noDictionaries));
    }

    void expectTwoDictionariesLoad()
    {
        EXPECT_CALL(*fileAccess, exists(filePath)).WillOnce(Return(true));
        EXPECT_CALL(*fileAccess, readContent(filePath)).WillOnce(Return("some content"));
        EXPECT_CALL(*serializer, deserialize("some content")).WillOnce(Return(twoDictionaries));
    }

    void expectSerializeDictionaries(const Dictionaries& dictionaries)
    {
        EXPECT_CALL(*fileAccess, exists(filePath)).WillOnce(Return(true));
        EXPECT_CALL(*serializer, serialize(dictionaries)).WillOnce(Return("dictionaries"));
        EXPECT_CALL(*fileAccess, write(filePath, "dictionaries"));
    }

    std::shared_ptr<common::FileAccessMock> fileAccess =
        std::make_shared<StrictMock<common::FileAccessMock>>();
    std::shared_ptr<serialization::DictionarySerializerMock> serializer =
        std::make_shared<StrictMock<serialization::DictionarySerializerMock>>();
};

TEST_F(DictionaryPersistentStorageTest, givenPersistentStorageWithEmptyFile_shouldBeEmpty)
{
    EXPECT_CALL(*fileAccess, exists(filePath)).WillOnce(Return(true));
    EXPECT_CALL(*fileAccess, readContent(filePath)).WillOnce(Return(""));
    EXPECT_CALL(*serializer, deserialize("")).WillOnce(Return(Dictionaries{}));
    DictionaryPersistentStorage persistentStorage{fileAccess, serializer};

    ASSERT_TRUE(persistentStorage.empty());
}

TEST_F(DictionaryPersistentStorageTest, givenPersistentStorageWithFileWithDictionaries_shouldLoadDictionaries)
{
    expectTwoDictionariesLoad();
    DictionaryPersistentStorage persistentStorage{fileAccess, serializer};

    const auto actualDictionaries = persistentStorage.getDictionaries();

    ASSERT_EQ(actualDictionaries, twoDictionaries);
}

TEST_F(DictionaryPersistentStorageTest, givenInvalidFile_shouldReturnNoDictionaries)
{
    EXPECT_CALL(*fileAccess, exists(filePath)).WillOnce(Return(false));
    DictionaryPersistentStorage persistentStorage{fileAccess, serializer};

    const auto actualDictionaries = persistentStorage.getDictionaries();

    EXPECT_TRUE(actualDictionaries.empty());
}

TEST_F(DictionaryPersistentStorageTest, givenDictionaryAdditionByName_shouldAddEmptyDictionaryAndSerialize)
{
    expectNoDictionariesLoad();
    DictionaryPersistentStorage persistentStorage{fileAccess, serializer};
    expectSerializeDictionaries(dictionariesWithOneEmptyDictionary);

    persistentStorage.addDictionary(dictionaryName1);

    ASSERT_EQ(*persistentStorage.getDictionary(dictionaryName1), emptyDictionary1);
}

TEST_F(DictionaryPersistentStorageTest, givenDictionaryAddition_shouldAddDictionaryAndSerialize)
{
    expectNoDictionariesLoad();
    DictionaryPersistentStorage persistentStorage{fileAccess, serializer};
    expectSerializeDictionaries(dictionariesWithOneDictionary);

    persistentStorage.addDictionary(dictionary1);

    ASSERT_EQ(*persistentStorage.getDictionary(dictionaryName1), dictionary1);
}

TEST_F(DictionaryPersistentStorageTest,
       givenDictionaryAdditionByNameAndNonExistingFile_shouldAddEmptyDictionaryAndNotSerialize)
{
    EXPECT_CALL(*fileAccess, exists(filePath)).WillOnce(Return(false));
    DictionaryPersistentStorage persistentStorage{fileAccess, serializer};
    EXPECT_CALL(*fileAccess, exists(filePath)).WillOnce(Return(false));

    persistentStorage.addDictionary(dictionaryName1);

    ASSERT_EQ(*persistentStorage.getDictionary(dictionaryName1), emptyDictionary1);
}

TEST_F(DictionaryPersistentStorageTest,
       givenDictionaryAdditionAndNonExistingFile_shouldAddDictionaryAndNotSerialize)
{
    EXPECT_CALL(*fileAccess, exists(filePath)).WillOnce(Return(false));
    DictionaryPersistentStorage persistentStorage{fileAccess, serializer};
    EXPECT_CALL(*fileAccess, exists(filePath)).WillOnce(Return(false));

    persistentStorage.addDictionary(dictionary1);

    ASSERT_EQ(*persistentStorage.getDictionary(dictionaryName1), dictionary1);
}

TEST_F(DictionaryPersistentStorageTest, givenExistingDictionaryName_shouldReturnThisDictionary)
{
    expectTwoDictionariesLoad();
    DictionaryPersistentStorage persistentStorage{fileAccess, serializer};

    const auto actualDictionary = persistentStorage.getDictionary(dictionaryName1);

    ASSERT_EQ(*actualDictionary, dictionary1);
}

TEST_F(DictionaryPersistentStorageTest, givenNonExistingDictionary_shouldNotAddWordToDictionary)
{
    expectNoDictionariesLoad();
    DictionaryPersistentStorage persistentStorage{fileAccess, serializer};
    expectSerializeDictionaries(noDictionaries);

    persistentStorage.addWordToDictionary(dictionaryWord1, dictionaryName1);

    ASSERT_EQ(persistentStorage.getDictionary(dictionaryName1), boost::none);
}

TEST_F(DictionaryPersistentStorageTest,
       givenExistingWordInDictionary_shouldNotAddWordToDictionaryAndSerialize)
{
    expectTwoDictionariesLoad();
    DictionaryPersistentStorage persistentStorage{fileAccess, serializer};
    expectSerializeDictionaries(twoDictionaries);

    persistentStorage.addWordToDictionary(dictionaryWord1, dictionaryName1);

    const auto actualDictionary = persistentStorage.getDictionary(dictionaryName1);
    ASSERT_EQ(actualDictionary->words, dictionaryWords1);
}

TEST_F(DictionaryPersistentStorageTest, givenExistingDictionary_shouldAddWordToDictionaryAndSerialize)
{
    expectTwoDictionariesLoad();
    DictionaryPersistentStorage persistentStorage{fileAccess, serializer};
    expectSerializeDictionaries(twoDictionariesAfterAddition);

    persistentStorage.addWordToDictionary(dictionaryWord4, dictionaryName1);

    const auto actualDictionary = persistentStorage.getDictionary(dictionaryName1);
    ASSERT_EQ(actualDictionary->words, dictionaryWords1AfterAddition);
}

TEST_F(DictionaryPersistentStorageTest,
       givenExistingDictionaryAndNotExistingFile_shouldAddWordToDictionaryAndNotSerialize)
{
    expectTwoDictionariesLoad();
    DictionaryPersistentStorage persistentStorage{fileAccess, serializer};
    EXPECT_CALL(*fileAccess, exists(filePath)).WillOnce(Return(false));

    persistentStorage.addWordToDictionary(dictionaryWord4, dictionaryName1);

    const auto actualDictionary = persistentStorage.getDictionary(dictionaryName1);
    ASSERT_EQ(actualDictionary->words, dictionaryWords1AfterAddition);
}

TEST_F(DictionaryPersistentStorageTest, givenNonExistingDictionary_shouldNotRemoveDictionaryAndSerialize)
{
    expectNoDictionariesLoad();
    DictionaryPersistentStorage persistentStorage{fileAccess, serializer};
    expectSerializeDictionaries(noDictionaries);

    persistentStorage.removeDictionary(dictionaryName1);
}

TEST_F(DictionaryPersistentStorageTest, givenExistingDictionary_shouldRemoveDictionaryAndSerialize)
{
    expectTwoDictionariesLoad();
    DictionaryPersistentStorage persistentStorage{fileAccess, serializer};
    expectSerializeDictionaries(dictionariesAfterRemoval);

    persistentStorage.removeDictionary(dictionaryName1);

    ASSERT_EQ(persistentStorage.getDictionaries(), dictionariesAfterRemoval);
}

TEST_F(DictionaryPersistentStorageTest,
       givenExistingDictionaryAndNonExistingFile_shouldRemoveDictionaryAndNotSerialize)
{
    expectTwoDictionariesLoad();
    DictionaryPersistentStorage persistentStorage{fileAccess, serializer};
    EXPECT_CALL(*fileAccess, exists(filePath)).WillOnce(Return(false));

    persistentStorage.removeDictionary(dictionaryName2);

    ASSERT_EQ(persistentStorage.getDictionaries(), dictionariesWithOneDictionary);
}

TEST_F(DictionaryPersistentStorageTest,
       givenNonExistingDictionary_shouldNotRemoveWordFromDictionaryAndSerialize)
{
    expectNoDictionariesLoad();
    DictionaryPersistentStorage persistentStorage{fileAccess, serializer};
    expectSerializeDictionaries(noDictionaries);

    persistentStorage.removeWordFromDictionary(dictionaryWord1.englishWord, dictionaryName1);

    ASSERT_EQ(persistentStorage.getDictionary(dictionaryName1), boost::none);
}

TEST_F(DictionaryPersistentStorageTest,
       givenNonExistingWordInDictionary_shouldNotRemoveWordFromDictionaryAndSerialize)
{
    expectTwoDictionariesLoad();
    DictionaryPersistentStorage persistentStorage{fileAccess, serializer};
    expectSerializeDictionaries(twoDictionaries);

    persistentStorage.removeWordFromDictionary(dictionaryWord4.englishWord, dictionaryName1);

    const auto actualDictionary = persistentStorage.getDictionary(dictionaryName1);
    ASSERT_EQ(actualDictionary->words, dictionaryWords1);
}

TEST_F(DictionaryPersistentStorageTest,
       givenExistingWordInDictionary_shouldRemoveWordFromDictionaryAndSerialize)
{
    expectTwoDictionariesLoad();
    DictionaryPersistentStorage persistentStorage{fileAccess, serializer};
    expectSerializeDictionaries(twoDictionariesAfterRemoval);

    persistentStorage.removeWordFromDictionary(dictionaryWord1.englishWord, dictionaryName1);

    const auto actualDictionary = persistentStorage.getDictionary(dictionaryName1);
    ASSERT_EQ(actualDictionary->words, dictionaryWords1AfterRemoval);
}

TEST_F(DictionaryPersistentStorageTest,
       givenExistingWordInDictionaryAndNotExistingFile_shouldRemoveWordFromDictionaryAndNotSerialize)
{
    expectTwoDictionariesLoad();
    DictionaryPersistentStorage persistentStorage{fileAccess, serializer};
    EXPECT_CALL(*fileAccess, exists(filePath)).WillOnce(Return(false));

    persistentStorage.removeWordFromDictionary(dictionaryWord1.englishWord, dictionaryName1);

    const auto actualDictionary = persistentStorage.getDictionary(dictionaryName1);
    ASSERT_EQ(actualDictionary->words, dictionaryWords1AfterRemoval);
}

TEST_F(DictionaryPersistentStorageTest, givenNonExistingDictionary_shouldNotChangeWordTranslationAndSerialize)
{
    expectNoDictionariesLoad();
    DictionaryPersistentStorage persistentStorage{fileAccess, serializer};
    expectSerializeDictionaries(noDictionaries);

    persistentStorage.changeWordTranslationFromDictionary(dictionaryWord1.englishWord,
                                                          newDictionaryWordTranslation, dictionaryName1);

    ASSERT_EQ(persistentStorage.getDictionary(dictionaryName1), boost::none);
}

TEST_F(DictionaryPersistentStorageTest,
       givenExistingDictionaryAndExistingWord_shouldChangeWordTranslationInDictionaryAndSerialize)
{
    expectTwoDictionariesLoad();
    DictionaryPersistentStorage persistentStorage{fileAccess, serializer};
    expectSerializeDictionaries(twoDictionariesAfterTranslationChange);

    persistentStorage.changeWordTranslationFromDictionary(dictionaryWord1.englishWord,
                                                          newDictionaryWordTranslation, dictionaryName1);

    const auto actualDictionary = persistentStorage.getDictionary(dictionaryName1);
    ASSERT_EQ(actualDictionary->words, dictionaryWords1AfterTranslationChange);
}

TEST_F(DictionaryPersistentStorageTest,
       givenExistingDictionaryAndNotExistingFile_shouldChangeWordTranslationInDictionaryAndNotSerialize)
{
    expectTwoDictionariesLoad();
    DictionaryPersistentStorage persistentStorage{fileAccess, serializer};
    EXPECT_CALL(*fileAccess, exists(filePath)).WillOnce(Return(false));

    persistentStorage.changeWordTranslationFromDictionary(dictionaryWord1.englishWord,
                                                          newDictionaryWordTranslation, dictionaryName1);

    const auto actualDictionary = persistentStorage.getDictionary(dictionaryName1);
    ASSERT_EQ(actualDictionary->words, dictionaryWords1AfterTranslationChange);
}

TEST_F(DictionaryPersistentStorageTest, givenNonExistingDictionaryName_shouldReturnNone)
{
    expectTwoDictionariesLoad();
    DictionaryPersistentStorage persistentStorage{fileAccess, serializer};

    const auto actualDictionary = persistentStorage.getDictionary(nonExistingDictionaryName);

    ASSERT_EQ(actualDictionary, boost::none);
}

TEST_F(DictionaryPersistentStorageTest, givenNoDictionaries_shouldNotContainAnyDictionaries)
{
    expectNoDictionariesLoad();
    DictionaryPersistentStorage persistentStorage{fileAccess, serializer};

    ASSERT_FALSE(persistentStorage.containsDictionary(dictionaryName1));
    ASSERT_FALSE(persistentStorage.containsDictionary(dictionaryName2));
    ASSERT_FALSE(persistentStorage.containsDictionary(dictionaryName3));
    ASSERT_FALSE(persistentStorage.containsDictionary(nonExistingDictionaryName));
}

TEST_F(DictionaryPersistentStorageTest, givenTwoDictionaries_shouldContainTheseTwoDictionaries)
{
    expectTwoDictionariesLoad();
    DictionaryPersistentStorage persistentStorage{fileAccess, serializer};

    ASSERT_TRUE(persistentStorage.containsDictionary(dictionaryName1));
    ASSERT_TRUE(persistentStorage.containsDictionary(dictionaryName2));
}

TEST_F(DictionaryPersistentStorageTest, givenTwoDictionaries_shouldReturnSizeTwo)
{
    expectTwoDictionariesLoad();
    DictionaryPersistentStorage persistentStorage{fileAccess, serializer};

    ASSERT_EQ(persistentStorage.size(), 2);
}