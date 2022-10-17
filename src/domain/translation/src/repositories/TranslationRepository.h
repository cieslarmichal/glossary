#pragma once

#include <optional>
#include <vector>

#include "Translation.h"

namespace glossary::translation
{
class TranslationRepository
{
public:
    virtual ~TranslationRepository() = default;

    virtual void addTranslation(Translation) = 0;
    virtual std::optional<Translation> getTranslation(const std::string&) const = 0;
    virtual bool containsTranslation(const std::string&) const = 0;
};
}
