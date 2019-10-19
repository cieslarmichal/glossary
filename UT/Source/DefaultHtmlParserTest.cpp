#include "DefaultHtmlParser.h"

#include "gtest/gtest.h"

using namespace ::testing;

namespace
{
const std::string emptyHtmlContent{};
const std::string htmlContent{
    "\n\n<span class=\"ex-sent first-child t no-aq sents\">"
    "blackberry <span class=\"mw_t_wi\">wine</span></span>\n\n"};
const std::vector<std::string> expectedHtmlParsedContent{"blackberry wine"};
}

class DefaultHtmlParserTest : public Test
{
public:
    DefaultHtmlParser defaultHtmlParser;
};

TEST_F(DefaultHtmlParserTest, givenEmptyHtmlContent_shouldReturnEmptyString)
{
    const auto parsedHtmlContent = defaultHtmlParser.parse(emptyHtmlContent);

    ASSERT_TRUE(parsedHtmlContent.empty());
}

TEST_F(DefaultHtmlParserTest, givenHtmlContent_shouldReturnParsedContent)
{
    const auto parsedHtmlContent = defaultHtmlParser.parse(htmlContent);

    ASSERT_EQ(parsedHtmlContent, expectedHtmlParsedContent);
}
