#pragma once

#include <string>
#include <vector>

#include "Language.h"
#include "TranslatePayload.h"

namespace glossary::translation
{
class GoogleTranslateClient
{
public:
    virtual ~GoogleTranslateClient() = default;

    virtual std::string translate(const TranslatePayload&) const = 0;
};
}
