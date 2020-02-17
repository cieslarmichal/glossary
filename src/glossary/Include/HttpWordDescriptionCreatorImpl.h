#pragma once

#include <memory>

#include "DescriptionParser.h"
#include "EnglishWord.h"
#include "GlossaryHtmlParser.h"
#include "HttpWordDescriptionCreator.h"
#include "webConnection/HttpHandler.h"

class HttpWordDescriptionCreatorImpl : public HttpWordDescriptionCreator
{
public:
    HttpWordDescriptionCreatorImpl(
        std::unique_ptr<const webConnection::HttpHandler>,
        std::unique_ptr<const GlossaryHtmlParser>,
        std::unique_ptr<const DescriptionParser>);

    boost::optional<wordsDescriptionsDb::WordDescription>
    createWordDescription(
        const translationsDb::Translation&) const override;

private:
    boost::optional<std::string> getHttpContent(const EnglishWord&) const;

    std::unique_ptr<const webConnection::HttpHandler> httpHandler;
    std::unique_ptr<const GlossaryHtmlParser> glossaryParser;
    std::unique_ptr<const DescriptionParser> descriptionParser;

    static const std::string urlAddress;
};