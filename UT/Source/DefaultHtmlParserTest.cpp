#include "DefaultHtmlParser.h"

#include "gtest/gtest.h"

using namespace ::testing;

class DefaultHtmlParserTest : public Test
{
public:
    DefaultHtmlParser defaultHtmlParser;
};

TEST_F(DefaultHtmlParserTest, givenHtmlContent_shouldReturnParsedContent)
{
    const std::string taggedExample
            {"\n\n<span class=\"ex-sent first-child t no-aq sents\">"
             "blackberry <span class=\"mw_t_wi\">wine</span></span>\n\n"};
    const std::vector<std::string> exampleWithoutTags{"blackberry wine"};

    auto parsedHtmlContent = defaultHtmlParser.parse(taggedExample);

    ASSERT_EQ(parsedHtmlContent, exampleWithoutTags);
}

