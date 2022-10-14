#include "WordDescriptionServiceFactory.h"

#include "DefaultWordDescriptionServiceFactory.h"

namespace glossary::wordDescriptionService
{

std::unique_ptr<WordDescriptionServiceFactory>
WordDescriptionServiceFactory::createWordDescriptionServiceFactory(
    const std::shared_ptr<const common::fileSystem::FileAccess>& fileAccess)
{
    return std::make_unique<DefaultWordDescriptionServiceFactory>(fileAccess);
}

}