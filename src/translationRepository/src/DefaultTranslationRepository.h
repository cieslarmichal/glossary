#pragma once

#include <memory>

#include "TranslationRepository.h"
#include "TranslationsStorage.h"

namespace translationRepository
{
class DefaultTranslationRepository : public TranslationRepository
{
public:
    explicit DefaultTranslationRepository(std::unique_ptr<TranslationsStorage>);

    void addTranslation(Translation) override;
    boost::optional<Translation> getTranslation(const SourceText&) const override;

private:
    std::unique_ptr<TranslationsStorage> storage;
};
}
