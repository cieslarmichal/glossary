#include "DefaultWordDescriptionRepositoryFactory.h"

#include "DefaultWordDescriptionRepository.h"
#include "WordsDescriptionsJsonSerializer.h"
#include "WordsDescriptionsPersistentStorage.h"

namespace wordDescriptionRepository
{
DefaultWordDescriptionRepositoryFactory::DefaultWordDescriptionRepositoryFactory(
    std::shared_ptr<const utils::FileAccess> fileAccessInit)
    : fileAccess{std::move(fileAccessInit)}
{
}

std::unique_ptr<WordDescriptionRepository>
DefaultWordDescriptionRepositoryFactory::createWordDescriptionRepository() const
{
    return std::make_unique<DefaultWordDescriptionRepository>(
        std::make_unique<WordsDescriptionsPersistentStorage>(
            fileAccess, std::make_shared<WordsDescriptionsJsonSerializer>()));
}

}