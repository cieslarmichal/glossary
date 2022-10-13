#include "WordDescriptionRepositoryFactory.h"

#include "../../common/fileSystem/include/FileAccess.h"
#include "DefaultWordDescriptionRepositoryFactory.h"

namespace glossary::wordDescriptionRepository
{
std::unique_ptr<WordDescriptionRepositoryFactory>
WordDescriptionRepositoryFactory::createWordDescriptionRepositoryFactory(
    const std::shared_ptr<const common::FileAccess>& fileAccess)
{
    return std::make_unique<DefaultWordDescriptionRepositoryFactory>(fileAccess);
}
}
