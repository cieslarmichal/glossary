#include "GetRandomWordFromDictionaryQueryImpl.h"

#include "gtest/gtest.h"

#include "../repositories/DictionaryRepositoryMock.h"
#include "random/RandomNumberGeneratorMock.h"
#include "exceptions/DictionaryMissingWordsError.h"
#include "exceptions/DictionaryNotFoundError.h"

using namespace ::testing;
using namespace glossary::dictionary;

namespace
{
const std::string dictionaryName{"dictionaryName"};
const DictionaryWord dictionaryWord1{"englishWord1", std::string{"translation1"}};
const DictionaryWord dictionaryWord2{"englishWord2", std::string{"translation2"}};
const DictionaryWord dictionaryWord3{"englishWord3", std::nullopt};
const std::vector<DictionaryWord> dictionaryWords{dictionaryWord1, dictionaryWord2, dictionaryWord3};
const Dictionary emptyDictionary{dictionaryName, {}};
const Dictionary dictionary{dictionaryName, dictionaryWords};
}

class GetRandomWordFromDictionaryQueryImplTest : public Test
{
public:
    std::shared_ptr<DictionaryRepositoryMock> dictionaryRepository =
        std::make_shared<StrictMock<DictionaryRepositoryMock>>();

    std::shared_ptr<common::random::RandomNumberGeneratorMock> randomNumberGenerator =
        std::make_shared<StrictMock<common::random::RandomNumberGeneratorMock>>();

    GetRandomWordFromDictionaryQueryImpl query{dictionaryRepository, randomNumberGenerator};
};

TEST_F(GetRandomWordFromDictionaryQueryImplTest, givenNoDictionary_shouldThrow)
{
    EXPECT_CALL(*dictionaryRepository, getDictionary(dictionaryName)).WillOnce(Return(std::nullopt));

    ASSERT_THROW(query.getRandomWord(dictionaryName),exceptions::DictionaryNotFoundError);
}

TEST_F(GetRandomWordFromDictionaryQueryImplTest, givenNoWordsInDictionary_shouldThrow)
{
    EXPECT_CALL(*dictionaryRepository, getDictionary(dictionaryName)).WillOnce(Return(emptyDictionary));

    ASSERT_THROW(query.getRandomWord(dictionaryName),exceptions::DictionaryMissingWordsError);
}

TEST_F(GetRandomWordFromDictionaryQueryImplTest, givenWordsInDictionary_shouldReturnRandomWord)
{
    EXPECT_CALL(*dictionaryRepository, getDictionary(dictionaryName)).WillOnce(Return(dictionary));

    EXPECT_CALL(*randomNumberGenerator, generate(0, dictionary.words.size() - 1)).WillOnce(Return(0));

    const auto randomWord = query.getRandomWord(dictionaryName);

    ASSERT_EQ(randomWord, dictionaryWord1);
}
