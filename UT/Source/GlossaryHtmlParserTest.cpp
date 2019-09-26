#include "GlossaryHtmlParser.h"

#include "gtest/gtest.h"

using namespace ::testing;

namespace
{
const std::string taggedDefinition
        {"\n<span class=\"dt \">\n<span class=\"dtText\"><strong class=\"mw_t_bc\">: </strong>"
         "the alcoholic fermented juice of fresh grapes used as a beverage</span>\n</span>\n"
        };
const std::string taggedSentence
        {"\n<span class=\"t has-aq\">Several bottles of <em>wine </em>were reported to have been stolen "
         "by two men during overnight July 20-21 from Binny’s Beverage Depot.</span>\n"
        };
const std::string taggedExample
        {"\n\n<span class=\"ex-sent first-child t no-aq sents\">"
         "blackberry <span class=\"mw_t_wi\">wine</span></span>\n\n"
        };

const std::string definitionMark{": "};
const std::string exampleMark{"//"};
const std::string sentenceMark{"\""};
const std::string definitionWithoutTags{
        definitionMark + "the alcoholic fermented juice of fresh grapes used as a beverage"};
const std::string sentenceWithoutTags{sentenceMark + "Several bottles of wine were reported to have been stolen "
                                                     "by two men during overnight July 20-21 from Binny’s Beverage Depot." +
                                      sentenceMark};
const std::string exampleWithoutTags{exampleMark + "blackberry wine"};

}

class GlossaryHtmlParserTest : public Test
{
public:
    GlossaryHtmlParser htmlParser;
};

TEST_F(GlossaryHtmlParserTest, givenHtmlContentWithDefinitionSequenceAndExample_shouldReturnParsedContent)
{
    const std::string testHtmlContent{taggedDefinition + taggedSentence + taggedExample};
    const std::vector<std::string> testParsedContent{definitionWithoutTags, sentenceWithoutTags, exampleWithoutTags};

    auto parsedHtmlContent = htmlParser.parse(testHtmlContent);

    ASSERT_EQ(parsedHtmlContent, testParsedContent);
}

TEST_F(GlossaryHtmlParserTest, givenHtmlContentWithoutImportantLines_shouldReturnEmptyVector)
{
    const std::string contentWithoutImportantLines{"<div class=\"s-term-cnt border-box\">\n"
                                                   "<span class=\"search-bar-submit\"></span>\n"
                                                   "\n does not contain definitions, sentences\n"
                                                   "nor examples"};

    auto parsedHtmlContent = htmlParser.parse(contentWithoutImportantLines);

    for(auto x : parsedHtmlContent)
    {
        std::cout<<x<<std::endl;
    }

    ASSERT_EQ(parsedHtmlContent.size(), std::vector<std::string>::size_type(0));
}

