#include "WordDescriptionConcurrentGenerator.h"

#include "gtest/gtest.h"

#include "WordDescriptionRetrieverServiceMock.h"

#include "utils/StlOperators.h"

using namespace ::testing;
using namespace glossary;
using namespace wordDescriptionRepository;

namespace
{
const EnglishWord englishWord1{"englishWord1"};
const EnglishWord englishWord2{"englishWord2"};
const EnglishWord englishWord3{"englishWord3"};
const EnglishWords englishWords{englishWord1, englishWord2, englishWord3};
const WordDescription wordDescription1{englishWord1, Description{}};
const WordDescription wordDescription2{
    englishWord2,
    Description{DefinitionsWithExamples{DefinitionWithExample{Definition{"definition"}, Example{"example"}}},
                {}}};
const WordDescription wordDescription3{englishWord3, Description{}};
const WordsDescriptions expectedWordsDescriptions{wordDescription1, wordDescription2, wordDescription3};
}

class WordDescriptionGeneratorImplTest : public Test
{
public:
    std::unique_ptr<WordDescriptionRetrieverServiceMock> wordDescriptionServiceInit =
        std::make_unique<StrictMock<WordDescriptionRetrieverServiceMock>>();
    WordDescriptionRetrieverServiceMock* wordDescriptionService = wordDescriptionServiceInit.get();
    WordDescriptionConcurrentGenerator generator{std::move(wordDescriptionServiceInit)};
};

TEST_F(WordDescriptionGeneratorImplTest, givenEnglishWord_shouldReturnWordDescription)
{
    EXPECT_CALL(*wordDescriptionService, retrieveWordDescription(englishWord2))
        .WillOnce(Return(wordDescription2));

    const auto actualWordDescription = generator.generateWordDescription(englishWord2);

    ASSERT_EQ(actualWordDescription, wordDescription2);
}

TEST_F(WordDescriptionGeneratorImplTest,
       givenEnglishWords_shouldGenerateAmountOfWordsDescriptionsEqualAmountOfEnglishWords)
{
    EXPECT_CALL(*wordDescriptionService, retrieveWordDescription(englishWord1))
        .WillOnce(Return(wordDescription1));
    EXPECT_CALL(*wordDescriptionService, retrieveWordDescription(englishWord2))
        .WillOnce(Return(wordDescription2));
    EXPECT_CALL(*wordDescriptionService, retrieveWordDescription(englishWord3))
        .WillOnce(Return(wordDescription3));

    const auto actualWordsDescriptions = generator.generateWordsDescriptions(englishWords);

    ASSERT_TRUE(compareVectors(actualWordsDescriptions, expectedWordsDescriptions));
}
