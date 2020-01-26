#include "HtmlWordsCreatorImpl.h"

#include "HtmlParserMock.h"
#include "gmock/gmock.h"
#include "webConnection/HttpRequestHandlerMock.h"

#include "FileAccessImpl.h"
#include "TestVariables/ParsedHtmlContent.h"
#include "TestVariables/WordDescriptionFromParser.h"
#include "gtest/gtest.h"

using namespace ::testing;

namespace
{
const std::string urlAddress{"https://www.merriam-webster.com/dictionary/wine"};
const wordsDb::translationsDb::Translation wordWithTranslation{"wino", "wine"};
const std::string htmlContentFilePath{"../UT/TestTextFiles/HtmlContent.txt"};
const WordDescription expectedWord{wordWithTranslation.englishWord,
                                   wordWithTranslation.polishWord,
                                   wordDescriptionFromParser};
const webConnection::Response emptyHtmlResponse{};
const std::vector<std::string> emptyParsedHtmlContent{};
}

class HtmlWordsCreatorImplTest : public Test
{
    // TODO: change param from vector string to string in GlossaryHtmlParser
    // TODO: mock WordDescriptionParser
public:
    std::string prepareHtmlContent()
    {
        const FileAccessImpl fileAccess{};
        return fileAccess.readContent(htmlContentFilePath);
    }

    std::unique_ptr<webConnection::HttpRequestHandlerMock> httpHandlerInit =
        std::make_unique<StrictMock<webConnection::HttpRequestHandlerMock>>();
    webConnection::HttpRequestHandlerMock* httpHandler = httpHandlerInit.get();
    std::unique_ptr<HtmlParserMock> htmlParserInit =
        std::make_unique<StrictMock<HtmlParserMock>>();
    HtmlParserMock* htmlParser = htmlParserInit.get();
    HtmlWordsCreatorImpl creator{std::move(httpHandlerInit),
                                 std::move(htmlParserInit)};
};

TEST_F(HtmlWordsCreatorImplTest, givenEmptyHtmlContent_shouldNotCreateWord)
{
    EXPECT_CALL(*httpHandler, get(urlAddress))
        .WillOnce(Return(emptyHtmlResponse));
    EXPECT_CALL(*htmlParser, parse(emptyHtmlResponse.content))
        .WillOnce(Return(emptyParsedHtmlContent));

    const auto actualWord = creator.createWord(wordWithTranslation);

    ASSERT_FALSE(actualWord.is_initialized());
}

TEST_F(HtmlWordsCreatorImplTest, givenWordWithTranslation_shouldCreateWord)
{
    const auto htmlContent = prepareHtmlContent();
    webConnection::Response response{200, htmlContent};
    EXPECT_CALL(*httpHandler, get(urlAddress)).WillOnce(Return(response));
    EXPECT_CALL(*htmlParser, parse(htmlContent))
        .WillOnce(Return(testParsedHtmlContent));

    const auto actualWord = creator.createWord(wordWithTranslation);

    ASSERT_EQ(actualWord, expectedWord);
}
