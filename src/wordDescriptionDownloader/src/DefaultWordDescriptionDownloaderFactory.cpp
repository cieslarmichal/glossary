#include "DefaultWordDescriptionDownloaderFactory.h"

#include "DefaultWordDescriptionDownloader.h"
#include "WordsApiJsonResponseDeserializer.h"
#include "WordsApiResponseFetcher.h"

namespace glossary::wordDescriptionDownloader
{

DefaultWordDescriptionDownloaderFactory::DefaultWordDescriptionDownloaderFactory(
    std::shared_ptr<const httpClient::HttpClient> httpHandlerInit)
    : httpHandler{std::move(httpHandlerInit)}
{
}

std::unique_ptr<WordDescriptionDownloader>
DefaultWordDescriptionDownloaderFactory::createWordDescriptionDownloader() const
{
    return std::make_unique<DefaultWordDescriptionDownloader>(
        std::make_unique<WordsApiResponseFetcher>(httpHandler),
        std::make_unique<WordsApiJsonResponseDeserializer>());
}

}