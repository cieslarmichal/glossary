#pragma once

#include <memory>

#include "../clients/GoogleTranslateClient.h"
#include "queries/GetTranslationQuery.h"

namespace glossary::translation
{
class GetTranslationQueryImpl : public GetTranslationQuery
{
public:
    explicit GetTranslationQueryImpl(std::unique_ptr<GoogleTranslateClient>);

    std::optional<std::string> getTranslation(const GetTranslationQueryPayload&) const override;

private:
    std::unique_ptr<GoogleTranslateClient> googleTranslateClient;
};
}
