#include "WordDescriptionDownloaderFactory.h"

#include "DefaultWordDescriptionDownloaderFactory.h"

namespace wordDescriptionDownloader
{

std::unique_ptr<WordDescriptionDownloaderFactory>
WordDescriptionDownloaderFactory::createWordDescriptionDownloaderFactory(
    const std::shared_ptr<const webConnection::HttpHandler>& httpHandler)
{
    return std::make_unique<DefaultWordDescriptionDownloaderFactory>(httpHandler);
}

}