#include "HtmlWordsCreatorImpl.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "HtmlReaderMock.h"
#include "HtmlParserMock.h"

#include "StringHelper.h"
#include "FileAccessImpl.h"
#include "TestVariables/ParsedHtmlContent.h"
#include "TestVariables/WordDescriptionFromParser.h"

using namespace ::testing;

namespace
{
const std::string urlAddress{"https://www.merriam-webster.com/dictionary/wine"};
WordWithTranslation wordWithTranslation{"wine", "wino"};
const std::string htmlContentFilePath{"../UT/TestTextFiles/HtmlContent.txt"};
Word expectedWord{wordWithTranslation.englishWord, wordWithTranslation.polishTranslation, wordDescriptionFromParser};
}

class HtmlWordsCreatorImplTest : public Test
{
    //change param from vector string to string in GlossaryHtmlParser
public:
    std::string prepareHtmlContent()
    {
        const FileAccessImpl fileAccess{};
        return fileAccess.readContent(htmlContentFilePath);
    }

    std::unique_ptr<HtmlReaderMock> htmlReaderInit = std::make_unique<StrictMock<HtmlReaderMock>>();
    HtmlReaderMock * htmlReader = htmlReaderInit.get();
    std::unique_ptr<HtmlParserMock> htmlParserInit = std::make_unique<StrictMock<HtmlParserMock>>();
    HtmlParserMock * htmlParser = htmlParserInit.get();
    HtmlWordsCreatorImpl creator{std::move(htmlReaderInit), std::move(htmlParserInit)};
};

TEST_F(HtmlWordsCreatorImplTest, givenWordWithTranslation_shouldCreateWord)
{
    auto htmlContent = prepareHtmlContent();
    EXPECT_CALL(*htmlReader, read(urlAddress)).WillOnce(Return(htmlContent));
    EXPECT_CALL(*htmlParser, parse(htmlContent)).WillOnce(Return(testParsedHtmlContent));

    auto actualWord = creator.createWord(wordWithTranslation);

    ASSERT_EQ(actualWord, expectedWord);
}
