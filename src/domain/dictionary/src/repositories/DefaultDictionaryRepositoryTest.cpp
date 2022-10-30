#include "DefaultDictionaryRepository.h"

#include "gtest/gtest.h"

#include "../readers/DictionaryWordsCsvReaderMock.h"
#include "DictionaryStorageMock.h"

using namespace ::testing;
using namespace glossary::dictionary;

namespace
{
const std::string absoluteDictionaryWordsPath{"absoultePathToDictionaryWords.csv"};
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
const std::string newDictionaryWordTranslation{"newDictionaryWordTranslation"};
}

class DefaultDictionaryRepositoryTest : public Test
{
public:
    std::unique_ptr<DictionaryStorageMock> storageInit = std::make_unique<StrictMock<DictionaryStorageMock>>();
    DictionaryStorageMock* storage = storageInit.get();

    DefaultDictionaryRepository repository{std::move(storageInit)};
};

TEST_F(DefaultDictionaryRepositoryTest, shouldAddDictionaryByNameToStorage)
{
    EXPECT_CALL(*storage, addDictionary(dictionaryName1));

    repository.addDictionary(dictionaryName1);
}

TEST_F(DefaultDictionaryRepositoryTest, shouldAddDictionaryToStorage)
{
    EXPECT_CALL(*storage, addDictionary(dictionary1));

    repository.addDictionary(dictionary1);
}

TEST_F(DefaultDictionaryRepositoryTest, shouldAddWordToDictionaryInStorage)
{
    EXPECT_CALL(*storage, addWordToDictionary(dictionaryWord1, dictionaryName1));

    repository.addWordToDictionary(dictionaryWord1, dictionaryName1);
}

TEST_F(DefaultDictionaryRepositoryTest, shouldRemoveDictionaryFromStorage)
{
    EXPECT_CALL(*storage, removeDictionary(dictionaryName1));

    repository.removeDictionary(dictionaryName1);
}

TEST_F(DefaultDictionaryRepositoryTest, shouldRemoveWordFromDictionaryInStorage)
{
    EXPECT_CALL(*storage, removeWordFromDictionary(dictionaryWord1.englishWord, dictionaryName1));

    repository.removeWordFromDictionary(dictionaryWord1.englishWord, dictionaryName1);
}

TEST_F(DefaultDictionaryRepositoryTest, shouldChangeWordTranslationFromDictionaryInStorage)
{
    EXPECT_CALL(*storage, changeWordTranslationFromDictionary(dictionaryWord1.englishWord, newDictionaryWordTranslation,
                                                              dictionaryName1));

    repository.changeWordTranslationFromDictionary(dictionaryWord1.englishWord, newDictionaryWordTranslation,
                                                   dictionaryName1);
}

TEST_F(DefaultDictionaryRepositoryTest, givenDictionaryNameNonExistingInStorage_shouldReturnNone)
{
    EXPECT_CALL(*storage, getDictionary(dictionaryName1)).WillOnce(Return(std::nullopt));

    const auto actualDictionary = repository.getDictionary(dictionaryName1);

    ASSERT_EQ(actualDictionary, std::nullopt);
}

TEST_F(DefaultDictionaryRepositoryTest, givenDictionaryNameExistingInStorage_shouldReturnDictionary)
{
    EXPECT_CALL(*storage, getDictionary(dictionaryName1)).WillOnce(Return(dictionary1));

    const auto actualDictionary = repository.getDictionary(dictionaryName1);

    ASSERT_EQ(*actualDictionary, dictionary1);
}

TEST_F(DefaultDictionaryRepositoryTest, shouldReturnDictionariesFromStorage)
{
    EXPECT_CALL(*storage, getDictionaries()).WillOnce(Return(dictionaries));

    const auto actualDictionaries = repository.getDictionaries();

    ASSERT_EQ(actualDictionaries, dictionaries);
}

TEST_F(DefaultDictionaryRepositoryTest, givenDictionaryExistingInStorage_shouldContainThisDictionary)
{
    EXPECT_CALL(*storage, containsDictionary(dictionaryName2)).WillOnce(Return(true));

    ASSERT_TRUE(repository.containsDictionary(dictionaryName2));
}

TEST_F(DefaultDictionaryRepositoryTest, givenDictionaryNonExistingInStorage_shouldNotContainThisDictionary)
{
    EXPECT_CALL(*storage, containsDictionary(dictionaryName2)).WillOnce(Return(false));

    ASSERT_FALSE(repository.containsDictionary(dictionaryName2));
}
