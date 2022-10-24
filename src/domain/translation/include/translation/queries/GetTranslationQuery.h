#pragma once

#include <optional>
#include <string>

#include "GetTranslationQueryPayload.h"

namespace glossary::translation
{
class GetTranslationQuery
{
public:
    virtual ~GetTranslationQuery() = default;

    virtual std::optional<std::string> getTranslation(const GetTranslationQueryPayload&) const = 0;
};
}
