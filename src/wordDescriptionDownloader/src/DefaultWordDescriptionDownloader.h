#pragma once

#include <memory>

#include "DescriptionParser.h"
#include "LinesSelector.h"
#include "WordDescriptionDownloader.h"
#include "webConnection/HttpHandler.h"
#include "wordDescriptionRepository/EnglishWord.h"

namespace wordDescriptionDownloader
{
class DefaultWordDescriptionDownloader : public WordDescriptionDownloader
{
public:
    DefaultWordDescriptionDownloader(std::shared_ptr<const webConnection::HttpHandler>,
                                     std::unique_ptr<const LinesSelector>,
                                     std::unique_ptr<const DescriptionParser>);

    boost::optional<wordDescriptionRepository::WordDescription>
    downloadWordDescription(const wordDescriptionRepository::EnglishWord&) const override;

private:
    boost::optional<std::string> getHttpContent(const wordDescriptionRepository::EnglishWord&) const;

    std::shared_ptr<const webConnection::HttpHandler> httpHandler;
    std::unique_ptr<const LinesSelector> linesSelector;
    std::unique_ptr<const DescriptionParser> descriptionParser;

    static const std::string urlAddress;
};
}