#pragma once

#include <memory>

#include "TranslationsDb.h"
#include "TranslationsStorage.h"

namespace translationsDb
{
class TranslationsDbImpl : public TranslationsDb
{
public:
    explicit TranslationsDbImpl(std::unique_ptr<TranslationsStorage>);

    void addTranslation(Translation) override;
    boost::optional<Translation> getTranslation(const SourceText&) const override;
    Translations getTranslations() const override;

private:
    std::unique_ptr<TranslationsStorage> storage;
};
}
