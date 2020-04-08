#include "GoogleTranslateApiRequestFormatter.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace glossary::translator;

namespace
{
const std::string url{"https://translation.googleapis.com/language/translate/v2?"};
const std::string key = {"key=AIzaSyCzXw_W97vKC5sSHXpNSCSpB5STCZkk08o"};
const auto requestBase = url + key;
const auto sourceField = R"(&source=pl)";
const auto targetField = R"(&target=en)";
const webConnection::Request requestWithSingleWord = requestBase + "&q=piwo" + sourceField + targetField;
const webConnection::Request requestWithMultipleWord =
    requestBase + "&q=piwo+jest+pyszne" + sourceField + targetField;
const auto emptyText = "";
const auto singleWordText = "piwo";
const auto multipleWordsText = "piwo jest pyszne";
const auto sourceLanguage = SourceLanguage::Polish;
const auto targetLanguage = TargetLanguage::English;
}

class GoogleTranslateApiRequestFormatterTest : public Test
{
public:
    GoogleTranslateApiRequestFormatter formatter;
};

TEST_F(GoogleTranslateApiRequestFormatterTest, givenEmptyText_shouldReturnNone)
{
    const auto formattedRequest = formatter.getFormattedRequest(emptyText, sourceLanguage, targetLanguage);

    ASSERT_EQ(formattedRequest, boost::none);
}

TEST_F(GoogleTranslateApiRequestFormatterTest, givenOneWordText_shouldReturnRequestWithThisWordInTextField)
{
    const auto actualFormattedRequest =
        formatter.getFormattedRequest(singleWordText, sourceLanguage, targetLanguage);

    ASSERT_EQ(*actualFormattedRequest, requestWithSingleWord);
}

TEST_F(GoogleTranslateApiRequestFormatterTest,
       givenThreeWordsText_shouldReturnRequestWithTheseWordsSplitByPlusSignInTextField)
{
    const auto actualFormattedRequest =
        formatter.getFormattedRequest(multipleWordsText, sourceLanguage, targetLanguage);

    ASSERT_EQ(*actualFormattedRequest, requestWithMultipleWord);
}