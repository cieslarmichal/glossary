#pragma once

#include "Translation.h"

namespace glossary::translation
{
class TranslationsStorage
{
public:
    virtual ~TranslationsStorage() = default;

    virtual void addTranslation(Translation) = 0;
    virtual std::optional<Translation> getTranslation(const std::string&) const = 0;
    virtual std::vector<Translation> getTranslations() const = 0;
    virtual bool contains(const std::string&) const = 0;
    virtual std::vector<Translation>::size_type size() const = 0;
    virtual bool empty() const = 0;
};
}
