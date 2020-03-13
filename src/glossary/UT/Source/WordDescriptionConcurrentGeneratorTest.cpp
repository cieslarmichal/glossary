#include "WordDescriptionConcurrentGenerator.h"

#include "gtest/gtest.h"

#include "WordDescriptionServiceMock.h"
#include "boost/algorithm/cxx11/all_of.hpp"
#include "boost/algorithm/cxx11/any_of.hpp"

using namespace ::testing;
using namespace wordsDescriptionsDb;
using namespace boost::algorithm;

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
const boost::optional<WordDescription> wordDescription1Opt{wordDescription1};
const boost::optional<WordDescription> wordDescription2Opt{wordDescription2};
const WordsDescriptions expectedWordsDescriptions{wordDescription1, wordDescription2, wordDescription3};
}

class WordDescriptionGeneratorImplTest : public Test
{
public:
    std::unique_ptr<WordDescriptionServiceMock> wordDescriptionServiceInit =
        std::make_unique<StrictMock<WordDescriptionServiceMock>>();
    WordDescriptionServiceMock* wordDescriptionService = wordDescriptionServiceInit.get();
    WordDescriptionConcurrentGenerator generator{std::move(wordDescriptionServiceInit)};
};

TEST_F(WordDescriptionGeneratorImplTest,
       givenEnglishWordAndServiceDoesNotContainWordDescription_shouldReturnWordDescriptionWithNoDescription)
{
    EXPECT_CALL(*wordDescriptionService, getWordDescription(englishWord1)).WillOnce(Return(boost::none));

    const auto actualWordDescription = generator.generateWordDescription(englishWord1);

    ASSERT_EQ(actualWordDescription, wordDescription1);
}

TEST_F(WordDescriptionGeneratorImplTest,
       givenEnglishWordAndServiceContainsWordDescription_shouldReturnWordDescription)
{
    EXPECT_CALL(*wordDescriptionService, getWordDescription(englishWord2))
        .WillOnce(Return(wordDescription2Opt));

    const auto actualWordDescription = generator.generateWordDescription(englishWord2);

    ASSERT_EQ(actualWordDescription, wordDescription2);
}

TEST_F(WordDescriptionGeneratorImplTest,
       givenEnglishWords_shouldGenerateAmountOfWordsDescriptionsEqualAmountOfEnglishWords)
{
    EXPECT_CALL(*wordDescriptionService, getWordDescription(englishWord1))
        .WillOnce(Return(wordDescription1Opt));
    EXPECT_CALL(*wordDescriptionService, getWordDescription(englishWord2))
        .WillOnce(Return(wordDescription2Opt));
    EXPECT_CALL(*wordDescriptionService, getWordDescription(englishWord3)).WillOnce(Return(boost::none));

    const auto actualWordsDescriptions = generator.generateWordsDescriptions(englishWords);

    ASSERT_TRUE(all_of(actualWordsDescriptions, [&](const auto& wordDescription) {
      return any_of(expectedWordsDescriptions,
                    [&](const auto& expectedWordDescription) { return wordDescription == expectedWordDescription; });
    }));
}
