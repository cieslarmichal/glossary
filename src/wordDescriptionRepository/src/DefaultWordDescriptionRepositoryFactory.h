#pragma once

#include "WordDescriptionRepositoryFactory.h"

namespace wordDescriptionRepository
{
class DefaultWordDescriptionRepositoryFactory : public WordDescriptionRepositoryFactory
{
public:
    explicit DefaultWordDescriptionRepositoryFactory(std::shared_ptr<const utils::FileAccess>);

    std::unique_ptr<WordDescriptionRepository> createWordDescriptionRepository() const override;

private:
    std::shared_ptr<const utils::FileAccess> fileAccess;
};
}