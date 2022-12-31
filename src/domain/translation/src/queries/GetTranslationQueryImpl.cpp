#include "GetTranslationQueryImpl.h"

namespace glossary::translation
{
GetTranslationQueryImpl::GetTranslationQueryImpl(std::shared_ptr<GoogleTranslateClient> googleTranslateClientInit,
                                                 std::shared_ptr<TranslationRepository> translationRepositoryInit)
    : googleTranslateClient{std::move(googleTranslateClientInit)},
      translationRepository{std::move(translationRepositoryInit)}
{
}

std::optional<std::string>
GetTranslationQueryImpl::getTranslation(const glossary::translation::GetTranslationQueryPayload& payload) const
{
    const auto cachedTranslation = translationRepository->getTranslation(payload.text);

    if (cachedTranslation)
    {
        return cachedTranslation->translatedText;
    }

    auto translationFromGoogleTranslate =
        googleTranslateClient->translate({payload.text, payload.sourceLanguage, payload.targetLanguage});

    if (translationFromGoogleTranslate)
    {
        auto newTranslation = Translation{payload.text, *translationFromGoogleTranslate};

        translationRepository->addTranslation(newTranslation);

        return translationFromGoogleTranslate;
    }

    return std::nullopt;
}
}
