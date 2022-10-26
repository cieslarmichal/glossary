#include "GetTranslationQueryImpl.h"

#include "gtest/gtest.h"

#include "../clients/GoogleTranslateClientMock.h"
#include "../repositories/TranslationRepositoryMock.h"

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
const Translation translation{polishText, englishText};
const TranslatePayload translatePayload{polishText, sourceLanguage, targetLanguage};
}

class GetTranslationQueryImplTest : public Test
{
public:
    std::unique_ptr<GoogleTranslateClientMock> googleTranslateClientInit =
        std::make_unique<StrictMock<GoogleTranslateClientMock>>();
    GoogleTranslateClientMock* googleTranslateClient = googleTranslateClientInit.get();
    std::unique_ptr<TranslationRepositoryMock> translationRepositoryInit =
        std::make_unique<StrictMock<TranslationRepositoryMock>>();
    TranslationRepositoryMock* translationRepository = translationRepositoryInit.get();
    GetTranslationQueryImpl query{std::move(googleTranslateClientInit), std::move(translationRepositoryInit)};
};

TEST_F(GetTranslationQueryImplTest, givenTranslationInRepository_shouldReturnTranslationFromRepository)
{
    EXPECT_CALL(*translationRepository, getTranslation(polishText)).WillOnce(Return(translation));

    const auto actualTranslation = query.getTranslation({polishText, sourceLanguage, targetLanguage});

    ASSERT_EQ(actualTranslation, englishText);
}

TEST_F(GetTranslationQueryImplTest,
       givenNoTranslationInRepositoryAndNoTranslationFromTranslationClient_shouldReturnNone)
{
    EXPECT_CALL(*translationRepository, getTranslation(polishText)).WillOnce(Return(std::nullopt));

    EXPECT_CALL(*googleTranslateClient, translate(translatePayload)).WillOnce(Return(std::nullopt));

    const auto actualTranslation = query.getTranslation({polishText, sourceLanguage, targetLanguage});

    ASSERT_EQ(actualTranslation, std::nullopt);
}

TEST_F(
    GetTranslationQueryImplTest,
    givenNoTranslationInRepositoryAndTranslationFromTranslationClient_shouldReturnTranslationFromGoogleTranslateClient)
{
    EXPECT_CALL(*translationRepository, getTranslation(polishText)).WillOnce(Return(std::nullopt));
    EXPECT_CALL(*translationRepository, addTranslation(translation));

    EXPECT_CALL(*googleTranslateClient, translate(translatePayload)).WillOnce(Return(englishText));

    const auto actualTranslation = query.getTranslation({polishText, sourceLanguage, targetLanguage});

    ASSERT_EQ(actualTranslation, englishText);
}
