#pragma once

#include <memory>

#include "DescriptionParser.h"
#include "HtmlParser.h"
#include "HtmlWordsCreator.h"
#include "webConnection/HttpRequestHandler.h"

class HtmlWordsCreatorImpl : public HtmlWordsCreator
{
public:
    explicit HtmlWordsCreatorImpl(
        std::unique_ptr<const webConnection::HttpRequestHandler>,
        std::unique_ptr<const HtmlParser>);

    boost::optional<wordsDb::wordsDescriptionsDb::WordDescription>
    createWord(const wordsDb::translationsDb::Translation&) const override;

private:
    std::unique_ptr<const webConnection::HttpRequestHandler> httpHandler;
    std::unique_ptr<const HtmlParser> htmlParser;
    DescriptionParser descriptionParser;

    static const std::string urlAddress;
};