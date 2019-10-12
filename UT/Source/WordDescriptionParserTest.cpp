#include "WordDescriptionParser.h"

#include "gtest/gtest.h"

#include "StringHelper.h"

using namespace ::testing;

namespace
{
const auto exampleParsedHtmlContent{": the alcoholic fermented juice of fresh grapes used as a beverage\n"
                                    ": wine or a substitute used in Christian communion services\n"
                                    ": the alcoholic usually fermented juice of a plant product (such as a fruit) used as a beverage\n"
                                    "//blackberry wine\n"
                                    ": something that invigorates or intoxicates\n"
                                    "\"In addition to beer, a selection of local and national wines will be offered..\"\n"
                                    "\"Who doesn't love delicious food paired with your favorite wine?\""};

const std::vector<std::string> emptyParsedHtmlContent{};
DefinitionsWithExamples definitionsWithExamples{{"the alcoholic fermented juice of fresh grapes used as a beverage", boost::none},
                                                {"wine or a substitute used in Christian communion services",        boost::none},
                                                {"the alcoholic usually fermented juice of a plant product (such as a fruit) used as a beverage",
                                                                                                                     std::string{
                                                                                                                             "blackberry wine"}},
                                                {"something that invigorates or intoxicates",                        boost::none}};
Sentences sentences{{"In addition to beer, a selection of local and national wines will be offered.."},
                    {"Who doesn't love delicious food paired with your favorite wine?"}};
const WordDescription expectedWordDescription{definitionsWithExamples, sentences};
const WordDescription emptyWordDescription{};
}

class WordDescriptionParserTest : public Test
{
public:
    WordDescriptionParser parser;
};

TEST_F(WordDescriptionParserTest, givenEmptyHtmlContent_shouldReturnEmptyWordDescription)
{
    auto actualWordDescription = parser.parse(emptyParsedHtmlContent);

    EXPECT_EQ(actualWordDescription, emptyWordDescription);
}

TEST_F(WordDescriptionParserTest, givenParsedHtmlContent_shouldReturnWordDescription)
{
    auto parsedHtmlContent = stringHelper::getSplitLines(exampleParsedHtmlContent);

    auto actualWordDescription = parser.parse(parsedHtmlContent);

    EXPECT_EQ(actualWordDescription, expectedWordDescription);
}