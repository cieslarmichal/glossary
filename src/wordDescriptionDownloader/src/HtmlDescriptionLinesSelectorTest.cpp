#include "HtmlDescriptionLinesSelector.h"

#include "gtest/gtest.h"

#include "testVariables/HtmlContent.h"
#include "testVariables/ParsedGlossaryHtmlContent.h"

using namespace ::testing;
using namespace glossary::wordDescriptionDownloader;

namespace
{
const std::string definition{"\n<span class=\"dt \">\n<span class=\"dtText\"><strong "
                             "class=\"mw_t_bc\">: </strong>"
                             "the alcoholic fermented juice of fresh grapes used as a "
                             "beverage</span>\n</span>\n"};
const std::string sentence{"\n<span class=\"t has-aq\">Several bottles of <em>wine </em>were reported "
                           "to have been stolen "
                           "by two men during overnight July 20-21 from Binny’s Beverage "
                           "Depot.</span>\n"};
const std::string example{"\n\n<span class=\"ex-sent first-child t no-aq sents\">"
                          "blackberry <span class=\"mw_t_wi\">wine</span></span>\n\n"};

const std::string parsedDefinition{": the alcoholic fermented juice of fresh grapes used as a beverage"};
const std::string parsedSentence{"; Several bottles of wine were reported to have been stolen "
                                 "by two men during overnight July 20-21 from Binny’s Beverage Depot."};
const std::string parsedExample{"// blackberry wine"};

const std::string emptyHtmlContent{};
const std::string contentWithoutImportantLines{"<div class=\"s-term-cnt border-box\">\n"
                                               "<span class=\"search-bar-submit\"></span>\n"
                                               "\n does not contain definitions, sentences\n"
                                               "nor examples"};
}

class HtmlDescriptionLinesSelectorTest : public Test
{
public:
    HtmlDescriptionLinesSelector glossaryHtmlParser;
};

TEST_F(HtmlDescriptionLinesSelectorTest, givenEmptyHtmlContent_shouldEmptyString)
{
    const auto actualParsedHtmlContent = glossaryHtmlParser.selectLines(emptyHtmlContent);

    ASSERT_TRUE(actualParsedHtmlContent.empty());
}

TEST_F(HtmlDescriptionLinesSelectorTest,
       givenHtmlContentWithDefinitionSequenceAndExample_shouldReturnParsedContent)
{
    const std::string testHtmlContent{definition + sentence + example};
    const std::vector<std::string> testParsedContent{parsedDefinition, parsedSentence, parsedExample};

    const auto actualParsedHtmlContent = glossaryHtmlParser.selectLines(testHtmlContent);

    ASSERT_EQ(actualParsedHtmlContent, testParsedContent);
}

TEST_F(HtmlDescriptionLinesSelectorTest, givenRealHtmlContent_shouldReturnParsedContent)
{
    const auto actualParsedHtmlContent = glossaryHtmlParser.selectLines(htmlContent);

    ASSERT_EQ(actualParsedHtmlContent, testParsedGlossaryHtmlContent);
}

TEST_F(HtmlDescriptionLinesSelectorTest, givenHtmlContentWithoutImportantLines_shouldReturnEmptyVector)
{
    const auto actualParsedHtmlContent = glossaryHtmlParser.selectLines(contentWithoutImportantLines);

    ASSERT_TRUE(actualParsedHtmlContent.empty());
}
