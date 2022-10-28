#include "GetRandomWordFromDictionariesQueryImpl.h"

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

class GetRandomWordFromDictionariesQueryImplTest : public Test
{
public:
    std::shared_ptr<DictionaryRepositoryMock> dictionaryRepository =
        std::make_shared<StrictMock<DictionaryRepositoryMock>>();

    std::shared_ptr<common::random::RandomNumberGeneratorMock> randomNumberGenerator =
        std::make_shared<StrictMock<common::random::RandomNumberGeneratorMock>>();

    GetRandomWordFromDictionariesQueryImpl query{dictionaryRepository, randomNumberGenerator};
};

TEST_F(GetRandomWordFromDictionariesQueryImplTest, givenNoWordsInDictionaries_shouldThrow)
{
    const std::vector<Dictionary> dictionariesWithoutWords{emptyDictionary};

    EXPECT_CALL(*dictionaryRepository, getDictionaries()).WillOnce(Return(dictionariesWithoutWords));

    ASSERT_THROW(query.getRandomWord(), exceptions::DictionaryMissingWordsError);
}

TEST_F(GetRandomWordFromDictionariesQueryImplTest, givenWordsInDictionary_shouldReturnRandomWord)
{
    const std::vector<Dictionary> dictionaries{dictionary};

    EXPECT_CALL(*dictionaryRepository, getDictionaries()).WillOnce(Return(dictionaries));

    EXPECT_CALL(*randomNumberGenerator, generate(0, dictionary.words.size() - 1)).WillOnce(Return(0));

    const auto randomWord = query.getRandomWord();

    ASSERT_EQ(randomWord, dictionaryWord1);
}
