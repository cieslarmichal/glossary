#pragma once

#include <memory>

#include "queries/GetSupportedLanguagesQuery.h"

namespace glossary::translation
{
class GetSupportedLanguagesQueryImpl : public GetSupportedLanguagesQuery
{
public:
    std::vector<Language> getSupportedLanguages() const override;
};
}
