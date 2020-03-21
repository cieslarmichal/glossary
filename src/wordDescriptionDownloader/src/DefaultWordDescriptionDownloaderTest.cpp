#include "DefaultWordDescriptionDownloader.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "DescriptionParserMock.h"
#include "LinesSelectorMock.h"
#include "webConnection/HttpHandlerMock.h"

#include "testVariables/HtmlContent.h"
#include "testVariables/ParsedGlossaryHtmlContent.h"
#include "testVariables/WordDescriptionFromParser.h"

using namespace ::testing;
using namespace wordDescriptionDownloader;

namespace
{
const std::string urlAddress{"https://www.merriam-webster.com/dictionary/fetch"};
const wordsDescriptionsDb::EnglishWord englishWord{"fetch"};
const WordDescription expectedWordDescription{englishWord, wordDescriptionFromParser};
const webConnection::Response emptyHtmlResponse{};
const std::vector<std::string> emptyParsedHtmlContent{};
}

class DefaultWordDescriptionDownloaderTest : public Test
{
public:
    std::unique_ptr<webConnection::HttpHandlerMock> httpHandlerInit =
        std::make_unique<StrictMock<webConnection::HttpHandlerMock>>();
    webConnection::HttpHandlerMock* httpHandler = httpHandlerInit.get();
    std::unique_ptr<LinesSelectorMock> linesSelectorInit = std::make_unique<StrictMock<LinesSelectorMock>>();
    LinesSelectorMock* linesSelector = linesSelectorInit.get();
    std::unique_ptr<DescriptionParserMock> descriptionParserInit =
        std::make_unique<StrictMock<DescriptionParserMock>>();
    DescriptionParserMock* descriptionParser = descriptionParserInit.get();
    DefaultWordDescriptionDownloader downloader{std::move(httpHandlerInit), std::move(linesSelectorInit),
                                                std::move(descriptionParserInit)};
};

TEST_F(DefaultWordDescriptionDownloaderTest, givenEmptyHtmlContent_shouldNotCreateWordDescription)
{
    EXPECT_CALL(*httpHandler, get(urlAddress)).WillOnce(Return(emptyHtmlResponse));
    EXPECT_CALL(*linesSelector, selectLines(emptyHtmlResponse.content))
        .WillOnce(Return(emptyParsedHtmlContent));
    EXPECT_CALL(*descriptionParser, parse(emptyParsedHtmlContent)).WillOnce(Return(boost::none));

    const auto actualWord = downloader.downloadWordDescription(englishWord);

    ASSERT_EQ(actualWord, boost::none);
}

TEST_F(DefaultWordDescriptionDownloaderTest, givenWordWithTranslation_shouldCreateWordDescription)
{
    webConnection::Response response{200, htmlContent};
    EXPECT_CALL(*httpHandler, get(urlAddress)).WillOnce(Return(response));
    EXPECT_CALL(*linesSelector, selectLines(htmlContent)).WillOnce(Return(testParsedGlossaryHtmlContent));
    EXPECT_CALL(*descriptionParser, parse(testParsedGlossaryHtmlContent))
        .WillOnce(Return(wordDescriptionFromParser));

    const auto actualWord = downloader.downloadWordDescription(englishWord);

    ASSERT_EQ(*actualWord, expectedWordDescription);
}
