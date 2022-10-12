#include "WordDescriptionDownloaderFactory.h"

#include "DefaultWordDescriptionDownloaderFactory.h"

namespace glossary::wordDescriptionDownloader
{
std::unique_ptr<WordDescriptionDownloaderFactory>
WordDescriptionDownloaderFactory::createWordDescriptionDownloaderFactory(
    const std::shared_ptr<const httpClient::HttpClient>& httpHandler)
{
    return std::make_unique<DefaultWordDescriptionDownloaderFactory>(httpHandler);
}
}