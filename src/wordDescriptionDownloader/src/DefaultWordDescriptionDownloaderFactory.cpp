#include "DefaultWordDescriptionDownloaderFactory.h"

#include "DefaultWordDescriptionDownloader.h"
#include "WordsApiJsonResponseDeserializer.h"
#include "WordsApiKeyFileReader.h"
#include "WordsApiResponseFetcher.h"

namespace glossary::wordDescriptionDownloader
{

DefaultWordDescriptionDownloaderFactory::DefaultWordDescriptionDownloaderFactory(
    std::shared_ptr<const webConnection::HttpHandler> httpHandlerInit,
    std::shared_ptr<const utils::FileAccess> fileAccessInit)
    : httpHandler{std::move(httpHandlerInit)}, fileAccess{std::move(fileAccessInit)}
{
}

std::unique_ptr<WordDescriptionDownloader>
DefaultWordDescriptionDownloaderFactory::createWordDescriptionDownloader() const
{
    return std::make_unique<DefaultWordDescriptionDownloader>(
        std::make_unique<WordsApiResponseFetcher>(httpHandler,
                                                  std::make_unique<WordsApiKeyFileReader>(fileAccess)),
        std::make_unique<WordsApiJsonResponseDeserializer>());
}

}