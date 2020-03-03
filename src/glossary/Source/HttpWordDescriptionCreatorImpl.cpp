#include "HttpWordDescriptionCreatorImpl.h"

#include "plog/Log.h"

#include "GlossaryHtmlParserImpl.h"
#include "webConnection/exceptions/ConnectionFailed.h"

const std::string HttpWordDescriptionCreatorImpl::urlAddress{"https://www.merriam-webster.com/dictionary/"};

HttpWordDescriptionCreatorImpl::HttpWordDescriptionCreatorImpl(
    std::shared_ptr<const webConnection::HttpHandler> htmlReaderInit,
    std::unique_ptr<const GlossaryHtmlParser> glossaryParserInit,
    std::unique_ptr<const DescriptionParser> descriptionParserInit)
    : httpHandler{std::move(htmlReaderInit)},
      glossaryParser{std::move(glossaryParserInit)},
      descriptionParser{std::move(descriptionParserInit)}
{
}

boost::optional<wordsDescriptionsDb::WordDescription> HttpWordDescriptionCreatorImpl::createWordDescription(
    const wordsDescriptionsDb::EnglishWord& englishWord) const
{
    LOG_DEBUG << "Creating word description from " << urlAddress << " for: " << englishWord;

    const auto httpContent = getHttpContent(englishWord);
    if (!httpContent)
    {
        return boost::none;
    }
    const auto linesWithDescription = glossaryParser->parse(*httpContent);

    if (const auto wordDescription = descriptionParser->parse(linesWithDescription))
    {
        return wordsDescriptionsDb::WordDescription{englishWord, *wordDescription};
    }
    return boost::none;
}

boost::optional<std::string>
HttpWordDescriptionCreatorImpl::getHttpContent(const EnglishWord& englishWord) const
{
    try
    {
        const auto response = httpHandler->get(urlAddress + englishWord);
        return response.content;
    }
    catch (const webConnection::exceptions::ConnectionFailed& e)
    {
        LOG_WARNING << "Get content from http failed: " << e.what();
        return boost::none;
    }
}
