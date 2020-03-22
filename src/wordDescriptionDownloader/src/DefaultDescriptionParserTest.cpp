#include "DefaultDescriptionParser.h"

#include "gtest/gtest.h"

#include "utils/StringHelper.h"
#include "utils/StlOperators.h"

using namespace ::testing;
using namespace wordDescriptionRepository;
using namespace wordDescriptionDownloader;

namespace
{
const auto exampleContent{":     the alcoholic fermented juice of fresh grapes used as a beverage\n"
                          ": wine or a substitute used in Christian communion services\n"
                          ": the alcoholic usually fermented juice of a plant product (such as a "
                          "fruit) used as a beverage    \n"
                          "// blackberry wine   \n"
                          ": something that invigorates or intoxicates\n"
                          ";     In addition to beer, a selection of local and national wines will "
                          "be offered..      \n"
                          "; Who doesn't love delicious food paired with your favorite wine?\n"
                          ": wine is a delicious beverage"};
const auto contentWithDuplications{":     the alcoholic fermented juice of fresh grapes used as a beverage\n"
                                   ": wine or a substitute used in Christian communion services\n"
                                   ": wine or a substitute used in Christian communion services\n"
                                   ": the alcoholic usually fermented juice of a plant product (such as a "
                                   "fruit) used as a beverage    \n"
                                   "// blackberry wine   \n"
                                   ": something that invigorates or intoxicates\n"
                                   ": something that invigorates or intoxicates\n"
                                   ";     In addition to beer, a selection of local and national wines will "
                                   "be offered..      \n"
                                   "; Who doesn't love delicious food paired with your favorite wine?\n"
                                   "; Who doesn't love delicious food paired with your favorite wine?\n"
                                   ": wine is a delicious beverage\n"
                                   ": wine is a delicious beverage"};
const DefinitionsWithExamples definitionsWithExamples{
    {"the alcoholic fermented juice of fresh grapes used as a beverage", boost::none},
    {"wine or a substitute used in Christian communion services", boost::none},
    {"the alcoholic usually fermented juice of a plant product (such as a "
     "fruit) used as a beverage",
     std::string{"blackberry wine"}},
    {"something that invigorates or intoxicates", boost::none},
    {"wine is a delicious beverage", boost::none}};
const Sentences sentences{{"In addition to beer, a selection of local and national wines will be "
                           "offered.."},
                          {"Who doesn't love delicious food paired with your favorite wine?"}};
const auto exampleContentPartlyWithoutMarks{
    ": the alcoholic fermented juice of fresh grapes used as a beverage\n"
    "wine or a substitute used in Christian communion services\n"
    "// blackberry wine\n"
    "strawberry wine\n"
    "In addition to beer, a selection of local and national wines will be "
    "offered..\n"
    "; Who doesn't love delicious food paired with your favorite wine?"};
const DefinitionsWithExamples someDefinitionsAndExamples{
    {"the alcoholic fermented juice of fresh grapes used as a beverage", boost::none}};
const Sentences someSentences{{"Who doesn't love delicious food paired with your favorite wine?"}};
const std::vector<std::string> emptyContent{};
}

class DefaultDescriptionParserTest : public Test
{
public:
    Description expectedDescription{definitionsWithExamples, sentences};
    Description descriptionPartlyComplete{someDefinitionsAndExamples, someSentences};

    DefaultDescriptionParser parser;
};

TEST_F(DefaultDescriptionParserTest, givenEmptyContent_shouldReturnNone)
{
    const auto actualDescriptionOpt = parser.parse(emptyContent);

    EXPECT_FALSE(actualDescriptionOpt);
}

TEST_F(DefaultDescriptionParserTest,
       givenHtmlContentWithoutSomeSpecificMarks_shouldReturnDescriptionWithSkippedSomeLines)
{
    const auto content = utils::getSplitLines(exampleContentPartlyWithoutMarks);

    auto actualDescriptionOpt = parser.parse(content);

    EXPECT_TRUE(compareDescriptions(*actualDescriptionOpt, descriptionPartlyComplete));
}

TEST_F(DefaultDescriptionParserTest, givenParsedHtmlContent_shouldReturnDescription)
{
    const auto content = utils::getSplitLines(exampleContent);

    auto actualDescriptionOpt = parser.parse(content);

    EXPECT_TRUE(compareDescriptions(*actualDescriptionOpt, expectedDescription));
}

TEST_F(DefaultDescriptionParserTest,
       givenParsedHtmlContentWithDuplications_shouldReturnDescriptionWithoutDuplications)
{
    const auto content = utils::getSplitLines(contentWithDuplications);

    auto actualDescriptionOpt = parser.parse(content);

    EXPECT_TRUE(compareDescriptions(*actualDescriptionOpt, expectedDescription));
}