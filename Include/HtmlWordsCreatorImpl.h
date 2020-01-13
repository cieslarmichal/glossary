#pragma once

#include <memory>

#include "HtmlParser.h"
#include "HtmlWordsCreator.h"
#include "webConnection/HttpRequestHandler.h"
#include "WordDescriptionParser.h"

class HtmlWordsCreatorImpl : public HtmlWordsCreator
{
public:
    explicit HtmlWordsCreatorImpl(std::unique_ptr<const webConnection::HttpRequestHandler>,
                                  std::unique_ptr<const HtmlParser>);

    boost::optional<Word> createWord(const WordWithTranslation&) const override;

private:
    std::unique_ptr<const webConnection::HttpRequestHandler> httpHandler;
    std::unique_ptr<const HtmlParser> htmlParser;
    WordDescriptionParser wordDescriptionParser;

    static const std::string urlAddress;
};