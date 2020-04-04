#include "DefaultDictionaryWordRandomizer.h"

#include "gtest/gtest.h"

#include "utils/RandomNumberGeneratorMock.h"

using namespace ::testing;
using namespace glossary;
using namespace dictionaryRepository;

namespace
{
const DictionaryWord dictionaryWord1{"englishWord1", std::string{"translation1"}};
const DictionaryWord dictionaryWord2{"englishWord2", std::string{"translation2"}};
const DictionaryWord dictionaryWord3{"englishWord3", boost::none};
const DictionaryWords emptyDictionaryWords{};
const DictionaryWords dictionaryWordsWithOneWord{dictionaryWord1};
const DictionaryWords dictionaryWords{dictionaryWord1, dictionaryWord2, dictionaryWord3};
const int wordsWithOneWordLastWordIndex{0};
const int wordsLastWordIndex{2};
}

class DefaultDictionaryWordRandomizerTest : public Test
{
public:
    std::shared_ptr<utils::RandomNumberGeneratorMock> randomNumberGenerator =
        std::make_shared<StrictMock<utils::RandomNumberGeneratorMock>>();
    DefaultDictionaryWordRandomizer wordRandomizer{randomNumberGenerator};
};

TEST_F(DefaultDictionaryWordRandomizerTest, givenNoDictionaryWords_shouldThrowInvalidArgument)
{
    ASSERT_THROW(wordRandomizer.randomize(emptyDictionaryWords), std::invalid_argument);
}

TEST_F(DefaultDictionaryWordRandomizerTest, givenOneDictionaryWord_shouldReturnThisDictionaryWord)
{
    EXPECT_CALL(*randomNumberGenerator, generate(0, wordsWithOneWordLastWordIndex)).WillOnce(Return(0));

    const auto actualRandomizedWord = wordRandomizer.randomize(dictionaryWordsWithOneWord);

    ASSERT_EQ(actualRandomizedWord, dictionaryWord1);
}

TEST_F(DefaultDictionaryWordRandomizerTest, givenDictionaryWords_shouldReturnOneOfDictionaryWords)
{
    EXPECT_CALL(*randomNumberGenerator, generate(0, wordsLastWordIndex)).WillOnce(Return(2));

    const auto actualRandomizedWord = wordRandomizer.randomize(dictionaryWords);

    ASSERT_EQ(actualRandomizedWord, dictionaryWord3);
}