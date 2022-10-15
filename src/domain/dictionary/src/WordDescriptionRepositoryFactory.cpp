#include "../include/WordDescriptionRepositoryFactory.h"

#include "DefaultWordDescriptionRepositoryFactory.h"

namespace glossary::dictionary
{
std::unique_ptr<WordDescriptionRepositoryFactory>
WordDescriptionRepositoryFactory::createWordDescriptionRepositoryFactory(
    const std::shared_ptr<const common::fileSystem::FileAccess>& fileAccess)
{
    return std::make_unique<DefaultWordDescriptionRepositoryFactory>(fileAccess);
}
}
