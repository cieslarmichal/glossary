#include "WordDescriptionDownloaderFactory.h"

#include "DefaultWordDescriptionDownloaderFactory.h"

namespace glossary::dictionary
{
std::unique_ptr<WordDescriptionDownloaderFactory>
WordDescriptionDownloaderFactory::createWordDescriptionDownloaderFactory(
    const std::shared_ptr<const common::httpClient::HttpClient>& httpHandler)
{
    return std::make_unique<DefaultWordDescriptionDownloaderFactory>(httpHandler);
}
}