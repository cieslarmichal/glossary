#include "WordDescriptionRepositoryFactory.h"

#include "DefaultWordDescriptionRepositoryFactory.h"
#include "utils/FileAccess.h"

namespace wordDescriptionRepository
{
std::unique_ptr<WordDescriptionRepositoryFactory>
WordDescriptionRepositoryFactory::createWordDescriptionRepositoryFactory(
    const std::shared_ptr<const utils::FileAccess>& fileAccess)
{
    return std::make_unique<DefaultWordDescriptionRepositoryFactory>(fileAccess);
}
}
