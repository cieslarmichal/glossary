#pragma once

#include "../include/WordDescriptionRepositoryFactory.h"

namespace glossary::dictionary
{
class DefaultWordDescriptionRepositoryFactory : public WordDescriptionRepositoryFactory
{
public:
    explicit DefaultWordDescriptionRepositoryFactory(std::shared_ptr<const common::fileSystem::FileAccess>);

    std::unique_ptr<WordDescriptionRepository> createWordDescriptionRepository() const override;

private:
    std::shared_ptr<const common::fileSystem::FileAccess> fileAccess;
};
}