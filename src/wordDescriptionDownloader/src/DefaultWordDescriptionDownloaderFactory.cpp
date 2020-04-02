#include "DefaultWordDescriptionDownloaderFactory.h"

#include "DefaultDescriptionParser.h"
#include "DefaultWordDescriptionDownloader.h"
#include "HtmlDescriptionLinesSelector.h"

namespace glossary::wordDescriptionDownloader
{

DefaultWordDescriptionDownloaderFactory::DefaultWordDescriptionDownloaderFactory(
    std::shared_ptr<const webConnection::HttpHandler> httpHandlerInit)
    : httpHandler{std::move(httpHandlerInit)}
{
}

std::unique_ptr<WordDescriptionDownloader>
DefaultWordDescriptionDownloaderFactory::createWordDescriptionDownloader() const
{
    return std::make_unique<DefaultWordDescriptionDownloader>(
        httpHandler, std::make_unique<HtmlDescriptionLinesSelector>(),
        std::make_unique<DefaultDescriptionParser>());
}

}