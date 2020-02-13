#include "HttpWordDescriptionCreatorImpl.h"

#include "DescriptionParserMock.h"
#include "GlossaryHtmlParserMock.h"
#include "gmock/gmock.h"
#include "webConnection/HttpRequestHandlerMock.h"

#include "TestVariables/ParsedGlossaryHtmlContent.h"
#include "TestVariables/WordDescriptionFromParser.h"
#include "gtest/gtest.h"
#include "utils/FileAccessImpl.h"

using namespace ::testing;

namespace
{
const std::string urlAddress{
    "https://www.merriam-webster.com/dictionary/fetch"};
const translationsDb::Translation wordWithTranslation{"sprowadzac",
                                                               "fetch"};
const std::string htmlContentFilePath{"../UT/TestTextFiles/HtmlContent.txt"};
const WordDescription expectedWordDescription{wordWithTranslation.englishWord,
                                              wordWithTranslation.polishWord,
                                              wordDescriptionFromParser};
const webConnection::Response emptyHtmlResponse{};
const std::vector<std::string> emptyParsedHtmlContent{};
}

class HttpWordDescriptionCreatorImplTest : public Test
{
public:
    std::string prepareHtmlContent()
    {
        const utils::FileAccessImpl fileAccess{};
        return fileAccess.readContent(htmlContentFilePath);
    }

    std::unique_ptr<webConnection::HttpRequestHandlerMock> httpHandlerInit =
        std::make_unique<StrictMock<webConnection::HttpRequestHandlerMock>>();
    webConnection::HttpRequestHandlerMock* httpHandler = httpHandlerInit.get();
    std::unique_ptr<GlossaryHtmlParserMock> glossaryParserInit =
        std::make_unique<StrictMock<GlossaryHtmlParserMock>>();
    GlossaryHtmlParserMock* glossaryParser = glossaryParserInit.get();
    std::unique_ptr<DescriptionParserMock> descriptionParserInit =
        std::make_unique<StrictMock<DescriptionParserMock>>();
    DescriptionParserMock* descriptionParser = descriptionParserInit.get();
    HttpWordDescriptionCreatorImpl creator{std::move(httpHandlerInit),
                                           std::move(glossaryParserInit),
                                           std::move(descriptionParserInit)};
};

TEST_F(HttpWordDescriptionCreatorImplTest,
       givenEmptyHtmlContent_shouldNotCreateWordDescription)
{
    EXPECT_CALL(*httpHandler, get(urlAddress))
        .WillOnce(Return(emptyHtmlResponse));
    EXPECT_CALL(*glossaryParser, parse(emptyHtmlResponse.content))
        .WillOnce(Return(emptyParsedHtmlContent));
    EXPECT_CALL(*descriptionParser, parse(emptyParsedHtmlContent))
        .WillOnce(Return(boost::none));

    const auto actualWord = creator.createWordDescription(wordWithTranslation);

    ASSERT_EQ(actualWord, boost::none);
}

TEST_F(HttpWordDescriptionCreatorImplTest,
       givenWordWithTranslation_shouldCreateWordDescription)
{
    const auto htmlContent = prepareHtmlContent();
    webConnection::Response response{200, htmlContent};
    EXPECT_CALL(*httpHandler, get(urlAddress)).WillOnce(Return(response));
    EXPECT_CALL(*glossaryParser, parse(htmlContent))
        .WillOnce(Return(testParsedGlossaryHtmlContent));
    EXPECT_CALL(*descriptionParser, parse(testParsedGlossaryHtmlContent))
        .WillOnce(Return(wordDescriptionFromParser));

    const auto actualWord = creator.createWordDescription(wordWithTranslation);

    ASSERT_EQ(*actualWord, expectedWordDescription);
}
