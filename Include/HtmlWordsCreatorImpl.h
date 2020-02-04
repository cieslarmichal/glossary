#pragma once

#include <memory>

#include "DescriptionParserImpl.h"
#include "GlossaryHtmlParser.h"
#include "HtmlWordsCreator.h"
#include "webConnection/HttpRequestHandler.h"

class HtmlWordsCreatorImpl : public HtmlWordsCreator
{
public:
    explicit HtmlWordsCreatorImpl(
        std::unique_ptr<const webConnection::HttpRequestHandler>,
        std::unique_ptr<const GlossaryHtmlParser>);

    boost::optional<wordsDb::wordsDescriptionsDb::WordDescription>
    createWord(const wordsDb::translationsDb::Translation&) const override;

private:
    std::unique_ptr<const webConnection::HttpRequestHandler> httpHandler;
    std::unique_ptr<const GlossaryHtmlParser> glossaryParser;
    DescriptionParserImpl descriptionParser;

    static const std::string urlAddress;
};