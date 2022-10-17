#pragma once

#include <optional>

#include "TranslationsStorage.h"

namespace glossary::translation
{
class TranslationsMemoryStorage : public TranslationsStorage
{
public:
    void addTranslation(Translation) override;
    std::optional<Translation> getTranslation(const std::string&) const override;
    std::vector<Translation> getTranslations() const override;
    bool contains(const std::string&) const override;
    std::vector<Translation>::size_type size() const override;
    bool empty() const override;

private:
    std::vector<Translation>::const_iterator findTranslationPosition(const std::string&) const;

    std::vector<Translation> translations;
};
}
