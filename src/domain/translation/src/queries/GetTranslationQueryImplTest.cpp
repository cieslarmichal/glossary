#include "GetTranslationQueryImpl.h"

#include "gtest/gtest.h"

#include "../clients/GoogleTranslateClientMock.h"

#include "collection/StlOperators.h"
#include "Language.h"

using namespace ::testing;
using namespace glossary::translation;

namespace
{
constexpr auto polishText = "szklanka";
constexpr auto englishText = "glass";
constexpr auto sourceLanguage = Language::Polish;
constexpr auto targetLanguage = Language::English;
const TranslatePayload translatePayload{polishText, sourceLanguage, targetLanguage};
}

class GetTranslationQueryImplTest : public Test
{
public:
    std::unique_ptr<GoogleTranslateClientMock> googleTranslateClientInit =
        std::make_unique<StrictMock<GoogleTranslateClientMock>>();
    GoogleTranslateClientMock* googleTranslateClient = googleTranslateClientInit.get();
    GetTranslationQueryImpl query{std::move(googleTranslateClientInit)};
};

TEST_F(GetTranslationQueryImplTest, getTranslation)
{
    EXPECT_CALL(*googleTranslateClient, translate(translatePayload)).WillOnce(Return(englishText));

    const auto translation = query.getTranslation({polishText, sourceLanguage, targetLanguage});

    ASSERT_EQ(translation, englishText);
}
