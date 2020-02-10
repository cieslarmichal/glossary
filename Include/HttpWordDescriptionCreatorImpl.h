#pragma once

#include <memory>

#include "DescriptionParser.h"
#include "GlossaryHtmlParser.h"
#include "HttpWordDescriptionCreator.h"
#include "webConnection/HttpRequestHandler.h"

class HttpWordDescriptionCreatorImpl : public HttpWordDescriptionCreator
{
public:
    HttpWordDescriptionCreatorImpl(
        std::unique_ptr<const webConnection::HttpRequestHandler>,
        std::unique_ptr<const GlossaryHtmlParser>,
        std::unique_ptr<const DescriptionParser>);

    boost::optional<wordsDb::wordsDescriptionsDb::WordDescription>
    createWordDescription(
        const wordsDb::translationsDb::Translation&) const override;

private:
    boost::optional<std::string> getHttpContent(const EnglishWord&) const;

    std::unique_ptr<const webConnection::HttpRequestHandler> httpHandler;
    std::unique_ptr<const GlossaryHtmlParser> glossaryParser;
    std::unique_ptr<const DescriptionParser> descriptionParser;

    static const std::string urlAddress;
};