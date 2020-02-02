#include "GlossaryHtmlParserImpl.h"

#include <StringHelper.h>

#include "FileAccessImpl.h"
#include "TestVariables/ParsedGlossaryHtmlContent.h"
#include "gtest/gtest.h"

using namespace ::testing;

namespace
{
const std::string definition{
    "\n<span class=\"dt \">\n<span class=\"dtText\"><strong "
    "class=\"mw_t_bc\">: </strong>"
    "the alcoholic fermented juice of fresh grapes used as a "
    "beverage</span>\n</span>\n"};
const std::string sentence{
    "\n<span class=\"t has-aq\">Several bottles of <em>wine </em>were reported "
    "to have been stolen "
    "by two men during overnight July 20-21 from Binny’s Beverage "
    "Depot.</span>\n"};
const std::string example{
    "\n\n<span class=\"ex-sent first-child t no-aq sents\">"
    "blackberry <span class=\"mw_t_wi\">wine</span></span>\n\n"};

const std::string parsedDefinition{
    ": the alcoholic fermented juice of fresh grapes used as a beverage"};
const std::string parsedSentence{
    "; Several bottles of wine were reported to have been stolen "
    "by two men during overnight July 20-21 from Binny’s Beverage Depot."};
const std::string parsedExample{ "// blackberry wine"};
const std::string htmlContentFilePath{"../UT/TestTextFiles/HtmlContent.txt"};
const std::string emptyHtmlContent{};
const std::string contentWithoutImportantLines{
    "<div class=\"s-term-cnt border-box\">\n"
    "<span class=\"search-bar-submit\"></span>\n"
    "\n does not contain definitions, sentences\n"
    "nor examples"};
}

class GlossaryHtmlParserImplTest : public Test
{
public:
    std::string prepareHtmlContent()
    {
        const FileAccessImpl fileAccess{};
        return fileAccess.readContent(htmlContentFilePath);
    }

    GlossaryHtmlParserImpl glossaryHtmlParser;
};

TEST_F(GlossaryHtmlParserImplTest, givenEmptyHtmlContent_shouldEmptyString)
{
    const auto actualParsedHtmlContent = glossaryHtmlParser.parse(emptyHtmlContent);

    ASSERT_TRUE(actualParsedHtmlContent.empty());
}

TEST_F(
    GlossaryHtmlParserImplTest,
    givenHtmlContentWithDefinitionSequenceAndExample_shouldReturnParsedContent)
{
    const std::string testHtmlContent{definition + sentence +
                                          example};
    const std::vector<std::string> testParsedContent{
        parsedDefinition, parsedSentence, parsedExample};

    const auto actualParsedHtmlContent = glossaryHtmlParser.parse(testHtmlContent);

    ASSERT_EQ(actualParsedHtmlContent, testParsedContent);
}

TEST_F(GlossaryHtmlParserImplTest, givenRealHtmlContent_shouldReturnParsedContent)
{
    const auto realHtmlContent = prepareHtmlContent();

    const auto actualParsedHtmlContent = glossaryHtmlParser.parse(realHtmlContent);

    ASSERT_EQ(actualParsedHtmlContent, testParsedGlossaryHtmlContent);
}

TEST_F(GlossaryHtmlParserImplTest,
       givenHtmlContentWithoutImportantLines_shouldReturnEmptyVector)
{
    const auto actualParsedHtmlContent =
        glossaryHtmlParser.parse(contentWithoutImportantLines);

    ASSERT_TRUE(actualParsedHtmlContent.empty());
}
