#include "TranslationYandexRequestFormatter.h"

#include "gtest/gtest.h"

using namespace ::testing;
using namespace glossary::translator;

namespace
{
const std::string url = R"(https://translate.yandex.net/api/v1.5/tr.json/translate?)";
const std::string key =
    R"(key=trnsl.1.1.20200113T184314Z.f0829944dec57123.a22eb90262e3bd9a179a881dc6960e0a7f142c8d&)";
const auto requestBase = url + key;
const auto langFields = R"(&lang=pl-en)";
const webConnection::Request requestWithSingleWord = requestBase + "text=piwo" + langFields;
const webConnection::Request requestWithMultipleWord = requestBase + "text=piwo+jest+pyszne" + langFields;
const auto emptyText = "";
const auto singleWordText = "piwo";
const auto multipleWordsText = "piwo jest pyszne";
const auto sourceLanguage = SourceLanguage::Polish;
const auto targetLanguage = TargetLanguage::English;
}

class TranslationYandexRequestFormatterTest : public Test
{
public:
    TranslationYandexRequestFormatter formatter;
};

TEST_F(TranslationYandexRequestFormatterTest, givenEmptyString_shouldReturnEmptyString)
{
    const auto formattedRequest = formatter.getFormattedRequest(emptyText, sourceLanguage, targetLanguage);

    ASSERT_TRUE(formattedRequest.empty());
}

TEST_F(TranslationYandexRequestFormatterTest, givenOneWordText_shouldReturnRequestWithThisWordInTextField)
{
    const auto actualFormattedRequest =
        formatter.getFormattedRequest(singleWordText, sourceLanguage, targetLanguage);

    ASSERT_EQ(actualFormattedRequest, requestWithSingleWord);
}

TEST_F(TranslationYandexRequestFormatterTest,
       givenThreeWordsText_shouldReturnRequestWithTheseWordsSplitByPlusSignInTextField)
{
    const auto actualFormattedRequest =
        formatter.getFormattedRequest(multipleWordsText, sourceLanguage, targetLanguage);

    ASSERT_EQ(actualFormattedRequest, requestWithMultipleWord);
}