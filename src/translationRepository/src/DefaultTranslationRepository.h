#pragma once

#include <memory>
#include <mutex>

#include "TranslationRepository.h"
#include "TranslationsStorage.h"

namespace glossary::translationRepository
{
class DefaultTranslationRepository : public TranslationRepository
{
public:
    explicit DefaultTranslationRepository(std::unique_ptr<TranslationsStorage>);

    void addTranslation(Translation) override;
    boost::optional<Translation> getTranslation(const SourceText&) const override;
    bool containsTranslation(const SourceText&) const override;

private:
    std::unique_ptr<TranslationsStorage> storage;
    mutable std::mutex lock;
};
}
