#include "GetWordDescriptionQueryImpl.h"

#include "gtest/gtest.h"

#include "../clients/WordsApiClientMock.h"
#include "../repositories/WordDescriptionRepositoryMock.h"

using namespace ::testing;
using namespace glossary::dictionary;

namespace
{
const std::string englishWord{"fetch"};
const std::vector<std::string> definitions{"be sold for a certain price",
                                                   "go or come after and bring or take back", "take away or remove",
                                                   "the action of fetching"};
const std::vector<std::string> examples{"The old print fetched a high price at the auction",
                                                "The dog fetched the hat", "The devil will fetch you!"};
const std::vector<std::string> synonyms{"bring", "bring in", "convey", "get"};
const WordDescription wordDescription{englishWord, definitions, examples, synonyms};
}

class GetWordDescriptionQueryImplTest : public Test
{
public:
    std::shared_ptr<WordDescriptionRepositoryMock> wordDescriptionRepository =
        std::make_shared<StrictMock<WordDescriptionRepositoryMock>>();

    std::unique_ptr<WordsApiClientMock> wordsApiClientInit = std::make_unique<StrictMock<WordsApiClientMock>>();
    WordsApiClientMock* wordsApiClient = wordsApiClientInit.get();

    GetWordDescriptionQueryImpl query{wordDescriptionRepository, std::move(wordsApiClientInit)};
};

TEST_F(GetWordDescriptionQueryImplTest, whenEnglishWordFoundInRepository_shouldReturnWordDescriptionFromRepository)
{
    EXPECT_CALL(*wordDescriptionRepository, getWordDescription(englishWord)).WillOnce(Return(wordDescription));

    const auto actualWordDescription = query.getWordDescription(englishWord);

    ASSERT_EQ(actualWordDescription, wordDescription);
}

TEST_F(GetWordDescriptionQueryImplTest, whenEnglishWordNotFoundInRepository_shouldReturnWordDescriptionFromWordsApiClient)
{
    EXPECT_CALL(*wordDescriptionRepository, getWordDescription(englishWord)).WillOnce(Return(std::nullopt));

    EXPECT_CALL(*wordsApiClient, getWordDefinitions(englishWord)).WillOnce(Return(definitions));
    EXPECT_CALL(*wordsApiClient, getWordExamples(englishWord)).WillOnce(Return(examples));
    EXPECT_CALL(*wordsApiClient, getWordSynonyms(englishWord)).WillOnce(Return(synonyms));

    EXPECT_CALL(*wordDescriptionRepository, addWordDescription(wordDescription));

    const auto actualWordDescription = query.getWordDescription(englishWord);

    ASSERT_EQ(actualWordDescription, wordDescription);
}
