#include "DefaultWordDescriptionDownloaderFactory.h"

#include "DefaultWordDescriptionDownloader.h"
#include "WordsApiJsonResponseDeserializer.h"
#include "WordsApiResponseFetcher.h"

namespace glossary::dictionary
{

DefaultWordDescriptionDownloaderFactory::DefaultWordDescriptionDownloaderFactory(
    std::shared_ptr<const common::httpClient::HttpClient> httpHandlerInit)
    : httpClient{std::move(httpHandlerInit)}
{
}

std::unique_ptr<WordDescriptionDownloader>
DefaultWordDescriptionDownloaderFactory::createWordDescriptionDownloader() const
{
    return std::make_unique<DefaultWordDescriptionDownloader>(
        std::make_unique<WordsApiResponseFetcher>(httpClient),
        std::make_unique<WordsApiJsonResponseDeserializer>());
}

}