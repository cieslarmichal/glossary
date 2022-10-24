#include "GetTranslationQueryImpl.h"

namespace glossary::translation
{
GetTranslationQueryImpl::GetTranslationQueryImpl(
    std::unique_ptr<GoogleTranslateClient> googleTranslateClientInit)
    : googleTranslateClient{std::move(googleTranslateClientInit)}
{
}

std::optional<std::string> GetTranslationQueryImpl::getTranslation(
    const glossary::translation::GetTranslationQueryPayload& payload) const
{
    return googleTranslateClient->translate({payload.text, payload.sourceLanguage, payload.targetLanguage});
}
}
