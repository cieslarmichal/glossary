#pragma once

#include <memory>

#include "../clients/GoogleTranslateClient.h"
#include "../repositories/TranslationRepository.h"
#include "queries/GetTranslationQuery.h"

namespace glossary::translation
{
class GetTranslationQueryImpl : public GetTranslationQuery
{
public:
    GetTranslationQueryImpl(std::unique_ptr<GoogleTranslateClient>, std::unique_ptr<TranslationRepository>);

    std::optional<std::string> getTranslation(const GetTranslationQueryPayload&) const override;

private:
    std::unique_ptr<GoogleTranslateClient> googleTranslateClient;
    std::unique_ptr<TranslationRepository> translationRepository;
};
}
