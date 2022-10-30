#include "DefaultWordDescriptionRepository.h"

#include "gtest/gtest.h"

#include "WordsDescriptionsStorageMock.h"

using namespace ::testing;
using namespace glossary::dictionary;

namespace
{
const std::string englishWord{"englishWord"};
const WordDescription wordDescription{englishWord, {}, {}, {}};
const std::vector<WordDescription> wordsDescriptions{wordDescription};
}

class DefaultWordDescriptionRepositoryTest : public Test
{
public:
    std::unique_ptr<WordsDescriptionsStorageMock> storageInit =
        std::make_unique<StrictMock<WordsDescriptionsStorageMock>>();
    WordsDescriptionsStorageMock* storage = storageInit.get();
    DefaultWordDescriptionRepository repository{std::move(storageInit)};
};

TEST_F(DefaultWordDescriptionRepositoryTest, givenWordDescritpionAddition_shouldAddWordDescriptionToStorage)
{
    EXPECT_CALL(*storage, addWordDescription(wordDescription));

    repository.addWordDescription(wordDescription);
}

TEST_F(DefaultWordDescriptionRepositoryTest, givenEnglishWordDescriptionNotExistingInStorage_shouldReturnNone)
{
    EXPECT_CALL(*storage, getWordDescription(englishWord)).WillOnce(Return(std::nullopt));

    const auto actualWord = repository.getWordDescription(englishWord);

    ASSERT_EQ(actualWord, std::nullopt);
}

TEST_F(DefaultWordDescriptionRepositoryTest, givenEnglishWordDescriptionExistingInStorage_shouldReturnWordDescription)
{
    EXPECT_CALL(*storage, getWordDescription(englishWord)).WillOnce(Return(wordDescription));

    const auto actualWord = repository.getWordDescription(englishWord);

    ASSERT_EQ(actualWord, wordDescription);
}

TEST_F(DefaultWordDescriptionRepositoryTest, givenEnglishWordExistingInStorage_shouldContainThisWordsDescription)
{
    EXPECT_CALL(*storage, contains(englishWord)).WillOnce(Return(true));

    ASSERT_TRUE(repository.contains(englishWord));
}

TEST_F(DefaultWordDescriptionRepositoryTest, givenEnglishWordNotExistingInStorage_shouldNotContainThisWordDescription)
{
    EXPECT_CALL(*storage, contains(englishWord)).WillOnce(Return(false));

    ASSERT_FALSE(repository.contains(englishWord));
}
