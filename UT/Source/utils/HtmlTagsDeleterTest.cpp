#include "utils/HtmlTagsDeleter.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace utils;

namespace
{
const std::vector<std::string> emptyHtmlContent{};
const std::vector<std::string> htmlContent{
    "\n\n<span class=\"ex-sent first-child t no-aq sents\">"
    "    blackberry <span class=\"mw_t_wi\">wine</span></span>\n\n"};
const std::vector<std::string> expectedHtmlParsedContent{"blackberry wine"};
const std::string htmlContentWithOpenWithoutEndHtmlTag{"<sdadsasdasdasd"};
const std::string htmlContentWithEndWithoutOpernHtmlTag{"sdads>asdasdasd"};
const std::vector<std::string> expected1{htmlContentWithOpenWithoutEndHtmlTag};
const std::vector<std::string> expected2{htmlContentWithEndWithoutOpernHtmlTag};
}

class HtmlTagsDeleterTest : public Test
{
public:
    HtmlTagsDeleter deleter;
};

TEST_F(HtmlTagsDeleterTest, givenEmptyHtmlContent_shouldReturnEmptyString)
{
    const auto parsedHtmlContent = deleter.deleteTags(emptyHtmlContent);

    ASSERT_TRUE(parsedHtmlContent.empty());
}

TEST_F(HtmlTagsDeleterTest,
       givenHtmlContentWithoutCloseTag_shouldNotRemoveAnything)
{
    const auto parsedHtmlContent = deleter.deleteTags(expected1);

    ASSERT_EQ(parsedHtmlContent, expected1);
}

TEST_F(HtmlTagsDeleterTest,
       givenHtmlContentWithoutOpenTag_shouldNotRemoveAnything)
{
    const auto parsedHtmlContent = deleter.deleteTags(expected2);

    ASSERT_EQ(parsedHtmlContent, expected2);
}

TEST_F(HtmlTagsDeleterTest, givenHtmlContent_shouldReturnTrimmedParsedContent)
{
    const auto parsedHtmlContent = deleter.deleteTags(htmlContent);

    ASSERT_EQ(parsedHtmlContent, expectedHtmlParsedContent);
}
