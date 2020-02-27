#include "HttpWordDescriptionCreatorImpl.h"

#include "DescriptionParserMock.h"
#include "GlossaryHtmlParserMock.h"
#include "gmock/gmock.h"
#include "webConnection/HttpHandlerMock.h"

#include "gtest/gtest.h"
#include "testVariables/ParsedGlossaryHtmlContent.h"
#include "testVariables/WordDescriptionFromParser.h"
#include "testVariables/HtmlContent.h"
#include "utils/FileAccessImpl.h"

using namespace ::testing;

namespace
{
const std::string urlAddress{
    "https://www.merriam-webster.com/dictionary/fetch"};
const wordsDescriptionsDb::EnglishWord englishWord{"fetch"};
const WordDescription expectedWordDescription{englishWord,
                                              wordDescriptionFromParser};
const webConnection::Response emptyHtmlResponse{};
const std::vector<std::string> emptyParsedHtmlContent{};
}

class HttpWordDescriptionCreatorImplTest : public Test
{
public:
    std::unique_ptr<webConnection::HttpHandlerMock> httpHandlerInit =
        std::make_unique<StrictMock<webConnection::HttpHandlerMock>>();
    webConnection::HttpHandlerMock* httpHandler = httpHandlerInit.get();
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

    const auto actualWord = creator.createWordDescription(englishWord);

    ASSERT_EQ(actualWord, boost::none);
}

TEST_F(HttpWordDescriptionCreatorImplTest,
       givenWordWithTranslation_shouldCreateWordDescription)
{
    webConnection::Response response{200, htmlContent};
    EXPECT_CALL(*httpHandler, get(urlAddress)).WillOnce(Return(response));
    EXPECT_CALL(*glossaryParser, parse(htmlContent))
        .WillOnce(Return(testParsedGlossaryHtmlContent));
    EXPECT_CALL(*descriptionParser, parse(testParsedGlossaryHtmlContent))
        .WillOnce(Return(wordDescriptionFromParser));

    const auto actualWord = creator.createWordDescription(englishWord);

    ASSERT_EQ(*actualWord, expectedWordDescription);
}
