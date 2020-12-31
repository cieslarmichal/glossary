#pragma once

#include <memory>

#include "TranslationRepository.h"
#include "utils/FileAccess.h"
#include "TranslationRepositoryApi.h"

namespace glossary::translationRepository
{
class TRANSLATOR_REPOSITORY_API TranslationRepositoryFactory
{
public:
    virtual ~TranslationRepositoryFactory() = default;

    virtual std::unique_ptr<TranslationRepository> createTranslationRepository() const = 0;

    static std::unique_ptr<TranslationRepositoryFactory>
    createTranslationRepositoryFactory(const std::shared_ptr<const utils::FileAccess>&);
};
}