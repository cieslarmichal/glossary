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
    GetTranslationQueryImpl(std::shared_ptr<GoogleTranslateClient>, std::shared_ptr<TranslationRepository>);

    std::optional<std::string> getTranslation(const GetTranslationQueryPayload&) const override;

private:
    std::shared_ptr<GoogleTranslateClient> googleTranslateClient;
    std::shared_ptr<TranslationRepository> translationRepository;
};
}
