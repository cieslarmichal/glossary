#pragma once

#include <memory>

#include "WordDescriptionDownloader.h"
#include "DescriptionParser.h"
#include "wordsDescriptionsDb/EnglishWord.h"
#include "LinesSelector.h"
#include "webConnection/HttpHandler.h"

namespace wordDescriptionDownloader
{
class DefaultWordDescriptionDownloader : public WordDescriptionDownloader
{
public:
    DefaultWordDescriptionDownloader(std::shared_ptr<const webConnection::HttpHandler>,
                                     std::unique_ptr<const LinesSelector>,
                                     std::unique_ptr<const DescriptionParser>);

    boost::optional<wordsDescriptionsDb::WordDescription>
    downloadWordDescription(const wordsDescriptionsDb::EnglishWord&) const override;

private:
    boost::optional<std::string> getHttpContent(const wordsDescriptionsDb::EnglishWord&) const;

    std::shared_ptr<const webConnection::HttpHandler> httpHandler;
    std::unique_ptr<const LinesSelector> linesSelector; // remove interface
    std::unique_ptr<const DescriptionParser> descriptionParser;

    static const std::string urlAddress;
};
}