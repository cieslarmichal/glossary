#pragma once

#include <memory>
#include "TranslationsDb.h"
#include "TranslationsStorage.h"

namespace wordsDb::translationsDb
{
class TranslationsDbImpl : public TranslationsDb
{
public:
    explicit TranslationsDbImpl(std::unique_ptr<TranslationsStorage>);

    void addTranslation(Translation) override;
    boost::optional<Translation>
    getTranslation(const PolishWord&) const override;
    Translations getTranslations() const override;

private:
    std::unique_ptr<TranslationsStorage> storage;
};
}
