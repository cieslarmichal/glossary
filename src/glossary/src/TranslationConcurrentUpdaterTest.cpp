#include "TranslationConcurrentUpdater.h"

#include "gtest/gtest.h"

#include "translation/queries/GetTranslationQueryMock.h"

#include "translation/Language.h"
#include "translation/Translation.h"

using namespace ::testing;
using namespace glossary;
using namespace translation;

namespace
{
const std::string englishWord1{"englishWord1"};
const std::string englishWord2{"englishWord2"};
const std::string englishWord3{"englishWord3"};
const std::string translatedText1{"translation1"};
const std::string translatedText3{"translation3"};
const std::vector<std::string> englishWords{englishWord1, englishWord2, englishWord3};
const Translation translation1{englishWord1, translatedText1};
const Language sourceLanguage = Language::English;
const Language targetLanguage = Language::Polish;
}

class TranslationConcurrentUpdaterTest : public Test
{
public:
    std::shared_ptr<GetTranslationQueryMock> getTranslationQuery =
        std::make_shared<StrictMock<GetTranslationQueryMock>>();
    TranslationConcurrentUpdater updater{getTranslationQuery};
};

TEST_F(TranslationConcurrentUpdaterTest, givenEnglishWords_shouldQueryTranslations)
{
    const auto expectedGetTranslationPayload1 = GetTranslationQueryPayload{englishWord1, sourceLanguage, targetLanguage};
    const auto expectedGetTranslationPayload2 = GetTranslationQueryPayload{englishWord2, sourceLanguage, targetLanguage};
    const auto expectedGetTranslationPayload3 = GetTranslationQueryPayload{englishWord3, sourceLanguage, targetLanguage};

    EXPECT_CALL(*getTranslationQuery, getTranslation(expectedGetTranslationPayload1))
        .WillOnce(Return(translatedText1));
    EXPECT_CALL(*getTranslationQuery, getTranslation(expectedGetTranslationPayload2))
        .WillOnce(Return(std::nullopt));
    EXPECT_CALL(*getTranslationQuery, getTranslation(expectedGetTranslationPayload3))
        .WillOnce(Return(translatedText3));

    updater.update(englishWords);
}
