#include "HttpWordDescriptionCreatorImpl.h"

#include <iostream>

#include "GlossaryHtmlParserImpl.h"
#include "exceptions/ConnectionFailed.h"
#include "webConnection/HttpRequestHandlerImpl.h"

const std::string HttpWordDescriptionCreatorImpl::urlAddress{
    "https://www.merriam-webster.com/dictionary/"};

HttpWordDescriptionCreatorImpl::HttpWordDescriptionCreatorImpl(
    std::unique_ptr<const webConnection::HttpRequestHandler> htmlReaderInit,
    std::unique_ptr<const GlossaryHtmlParser> glossaryParserInit,
    std::unique_ptr<const DescriptionParser> descriptionParserInit)
    : httpHandler{std::move(htmlReaderInit)}, glossaryParser{std::move(
                                                  glossaryParserInit)},
      descriptionParser{std::move(descriptionParserInit)}
{
}

boost::optional<wordsDb::wordsDescriptionsDb::WordDescription>
HttpWordDescriptionCreatorImpl::createWordDescription(
    const wordsDb::translationsDb::Translation& translation) const
{

    const auto httpContent = getHttpContent(translation.englishWord);
    if (!httpContent)
    {
        return boost::none;
    }
    const auto linesWithDescription = glossaryParser->parse(*httpContent);

    if (const auto wordDescription =
            descriptionParser->parse(linesWithDescription))
    {
        return wordsDb::wordsDescriptionsDb::WordDescription{translation.englishWord, translation.polishWord,
                               *wordDescription};
    }
    return boost::none;
}

boost::optional<std::string> HttpWordDescriptionCreatorImpl::getHttpContent(
    const EnglishWord& englishWord) const
{
    try
    {
        const auto response = httpHandler->get(urlAddress + englishWord);
        return response.content;
    }
    catch (const exceptions::ConnectionFailed& e)
    {
        std::cerr << e.what();
        return boost::none;
    }
}
