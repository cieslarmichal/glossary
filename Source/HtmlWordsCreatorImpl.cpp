#include "HtmlWordsCreatorImpl.h"

#include <iostream>

#include "GlossaryHtmlParser.h"
#include "exceptions/ConnectionFailed.h"
#include "webConnection/HttpRequestHandlerImpl.h"

const std::string HtmlWordsCreatorImpl::urlAddress{
    "https://www.merriam-webster.com/dictionary/"};

HtmlWordsCreatorImpl::HtmlWordsCreatorImpl(
    std::unique_ptr<const webConnection::HttpRequestHandler> htmlReaderInit,
    std::unique_ptr<const HtmlParser> htmlParserInit)
    : httpHandler{std::move(htmlReaderInit)}, htmlParser{
                                                  std::move(htmlParserInit)}
{
}

boost::optional<wordsDb::wordsDescriptionsDb::WordDescription>
HtmlWordsCreatorImpl::createWord(
    const wordsDb::translationsDb::Translation& wordWithTranslation) const
{
    std::string htmlContent;
    try
    {
        const auto response =
            httpHandler->get(urlAddress + wordWithTranslation.englishWord);
        htmlContent = response.content;
    }
    catch (const exceptions::ConnectionFailed& e)
    {
        std::cerr << e.what();
        return boost::none;
    }

    const auto parsedHtmlContent = htmlParser->parse(htmlContent);

    if (const auto wordDescription = descriptionParser.parse(parsedHtmlContent))
    {
        return wordsDb::wordsDescriptionsDb::WordDescription{
            wordWithTranslation.englishWord, wordWithTranslation.polishWord,
            *wordDescription};
    }
    return boost::none;
}
