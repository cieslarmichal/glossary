#pragma once

#include <memory>
#include <mutex>

#include "TranslationRepository.h"
#include "TranslationsStorage.h"

namespace glossary::translation
{
class DefaultTranslationRepository : public TranslationRepository
{
public:
    explicit DefaultTranslationRepository(std::unique_ptr<TranslationsStorage>);

    void addTranslation(Translation) override;
    std::optional<Translation> getTranslation(const std::string&) const override;
    bool containsTranslation(const std::string&) const override;

private:
    std::unique_ptr<TranslationsStorage> storage;
    mutable std::mutex lock;
};
}
