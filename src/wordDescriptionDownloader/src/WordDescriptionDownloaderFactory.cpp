#include "WordDescriptionDownloaderFactory.h"

#include "DefaultWordDescriptionDownloaderFactory.h"

namespace glossary::wordDescriptionDownloader
{
std::unique_ptr<WordDescriptionDownloaderFactory>
WordDescriptionDownloaderFactory::createWordDescriptionDownloaderFactory(
    const std::shared_ptr<const webConnection::HttpHandler>& httpHandler,
    const std::shared_ptr<const utils::FileAccess>& fileAccess)
{
    return std::make_unique<DefaultWordDescriptionDownloaderFactory>(httpHandler, fileAccess);
}
}