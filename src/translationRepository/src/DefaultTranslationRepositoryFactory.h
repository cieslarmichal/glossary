#pragma once

#include "TranslationRepositoryFactory.h"

namespace translationRepository
{
class DefaultTranslationRepositoryFactory : public TranslationRepositoryFactory
{
public:
    explicit DefaultTranslationRepositoryFactory(std::shared_ptr<const utils::FileAccess>);

    std::unique_ptr<TranslationRepository> createTranslationRepository() const override;

private:
    std::shared_ptr<const utils::FileAccess> fileAccess;
};
}
