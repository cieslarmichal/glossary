#include "DescriptionParserImpl.h"

#include "gtest/gtest.h"
#include "utils/StringHelper.h"

using namespace ::testing;
using namespace wordsDescriptionsDb;

namespace
{

const auto exampleContent{
    ":     the alcoholic fermented juice of fresh grapes used as a beverage\n"
    ": wine or a substitute used in Christian communion services\n"
    ": the alcoholic usually fermented juice of a plant product (such as a "
    "fruit) used as a beverage    \n"
    "// blackberry wine   \n"
    ": something that invigorates or intoxicates\n"
    ";     In addition to beer, a selection of local and national wines will "
    "be offered..      \n"
    "; Who doesn't love delicious food paired with your favorite wine?\n"
    ": wine is a delicious beverage"};
const DefinitionsWithExamples definitionsWithExamples{
    {"the alcoholic fermented juice of fresh grapes used as a beverage",
     boost::none},
    {"wine or a substitute used in Christian communion services", boost::none},
    {"the alcoholic usually fermented juice of a plant product (such as a "
     "fruit) used as a beverage",
     std::string{"blackberry wine"}},
    {"something that invigorates or intoxicates", boost::none},
    {"wine is a delicious beverage", boost::none}};
const Sentences sentences{
    {"In addition to beer, a selection of local and national wines will be "
     "offered.."},
    {"Who doesn't love delicious food paired with your favorite wine?"}};
const Description expectedWordDescription{definitionsWithExamples, sentences};

const auto exampleContentPartlyWithoutMarks{
    ": the alcoholic fermented juice of fresh grapes used as a beverage\n"
    "wine or a substitute used in Christian communion services\n"
    "// blackberry wine\n"
    "strawberry wine\n"
    "In addition to beer, a selection of local and national wines will be "
    "offered..\n"
    "; Who doesn't love delicious food paired with your favorite wine?"};

const DefinitionsWithExamples someDefinitionsAndExamples{
    {"the alcoholic fermented juice of fresh grapes used as a beverage",
     boost::none}};
const Sentences someSentences{
    {"Who doesn't love delicious food paired with your favorite wine?"}};
const Description wordDescriptionPartlyComplete{someDefinitionsAndExamples,
                                                someSentences};
const std::vector<std::string> emptyContent{};
}

class DescriptionParserImplTest : public Test
{
public:
    DescriptionParserImpl parser;
};

TEST_F(DescriptionParserImplTest,
       givenEmptyContent_shoulNotReturnWordDescription)
{
    const auto actualWordDescription = parser.parse(emptyContent);

    EXPECT_FALSE(actualWordDescription);
}

TEST_F(
    DescriptionParserImplTest,
    givenHtmlContentWithoutSomeSpecificMarks_shouldReturnWordDescriptionWithSkippedSomeLines)
{
    const auto content = utils::getSplitLines(exampleContentPartlyWithoutMarks);

    const auto actualWordDescription = parser.parse(content);

    EXPECT_EQ(actualWordDescription, wordDescriptionPartlyComplete);
}

TEST_F(DescriptionParserImplTest,
       givenParsedHtmlContent_shouldReturnWordDescription)
{
    const auto content = utils::getSplitLines(exampleContent);

    const auto actualWordDescription = parser.parse(content);

    EXPECT_EQ(actualWordDescription, expectedWordDescription);
}