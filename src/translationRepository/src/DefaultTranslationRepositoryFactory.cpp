#include "DefaultTranslationRepositoryFactory.h"

#include "DefaultTranslationRepository.h"
#include "TranslationsJsonSerializer.h"
#include "TranslationsPersistentStorage.h"

namespace glossary::translationRepository
{

DefaultTranslationRepositoryFactory::DefaultTranslationRepositoryFactory(
    std::shared_ptr<const utils::FileAccess> fileAccessInit)
    : fileAccess{std::move(fileAccessInit)}
{
}

std::unique_ptr<TranslationRepository>
DefaultTranslationRepositoryFactory::createTranslationRepository() const
{
    return std::make_unique<DefaultTranslationRepository>(std::make_unique<TranslationsPersistentStorage>(
        fileAccess, std::make_shared<TranslationsJsonSerializer>()));
}

}