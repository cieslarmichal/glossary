#include "HtmlTagsDeleter.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace utils;

namespace
{
const std::vector<std::string> emptyHtmlContent{};
const std::vector<std::string> contentWithTags{
    "&aasd\n;\n<span class=\"ex-sent first-child t no-aq sents\">\n&mdash;"
    "    & ;blackberry <span class=\"mw_t_wi\">wine</span></span>\n\n&;"};
const std::vector<std::string> expectedContentWithoutHtmlTags{"blackberry wine"};
const std::string content1{"<sdadsasdasdasd"};
const std::string content2{"sdads>asdasdasd"};
const std::string content3{"&sdad&sasd&&&asdasd&"};
const std::string content4{";sd;ads>asda;sdasd;"};
const std::vector<std::string> htmlContentWithStartingOnlyHtmlTag{content1};
const std::vector<std::string> htmlContentWithClosingOnlyHtmlTag{content2};
const std::vector<std::string> htmlContentWithStartingOnlyEntityHtmlTag{content3};
const std::vector<std::string> htmlContentWithClosingOnlyEntityHtmlTag{content4};
}

class HtmlTagsDeleterTest : public Test
{
public:
    HtmlTagsDeleter deleter;
};

TEST_F(HtmlTagsDeleterTest, givenEmptyHtmlContent_shouldReturnEmptyString)
{
    const auto actualContentWithoutTags = deleter.deleteTags(emptyHtmlContent);

    ASSERT_TRUE(actualContentWithoutTags.empty());
}

TEST_F(HtmlTagsDeleterTest, givenHtmlContentWithoutCloseTag_shouldNotRemoveAnything)
{
    const auto actualContentWithoutTags = deleter.deleteTags(htmlContentWithStartingOnlyHtmlTag);

    ASSERT_EQ(actualContentWithoutTags, htmlContentWithStartingOnlyHtmlTag);
}

TEST_F(HtmlTagsDeleterTest, givenHtmlContentWithoutOpenTag_shouldNotRemoveAnything)
{
    const auto actualContentWithoutTags = deleter.deleteTags(htmlContentWithClosingOnlyHtmlTag);

    ASSERT_EQ(actualContentWithoutTags, htmlContentWithClosingOnlyHtmlTag);
}

TEST_F(HtmlTagsDeleterTest, givenHtmlContentWithoutCloseEntityTag_shouldNotRemoveAnything)
{
    const auto actualContentWithoutTags = deleter.deleteTags(htmlContentWithStartingOnlyEntityHtmlTag);

    ASSERT_EQ(actualContentWithoutTags, htmlContentWithStartingOnlyEntityHtmlTag);
}

TEST_F(HtmlTagsDeleterTest, givenHtmlContentWithoutOpenEntityTag_shouldNotRemoveAnything)
{
    const auto actualContentWithoutTags = deleter.deleteTags(htmlContentWithClosingOnlyEntityHtmlTag);

    ASSERT_EQ(actualContentWithoutTags, htmlContentWithClosingOnlyEntityHtmlTag);
}

TEST_F(HtmlTagsDeleterTest, givenHtmlContent_shouldReturnHtmlTags)
{
    const auto actualContentWithoutTags = deleter.deleteTags(contentWithTags);

    ASSERT_EQ(actualContentWithoutTags, expectedContentWithoutHtmlTags);
}
