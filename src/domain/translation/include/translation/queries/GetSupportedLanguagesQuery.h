#pragma once

#include <optional>
#include <string>
#include <vector>

#include "Language.h"

namespace glossary::translation
{
class GetSupportedLanguagesQuery
{
public:
    virtual ~GetSupportedLanguagesQuery() = default;

    virtual std::vector<Language> getSupportedLanguages() const = 0;
};
}
