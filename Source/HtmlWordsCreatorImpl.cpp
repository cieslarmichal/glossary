#include <iostream>
#include "HtmlWordsCreatorImpl.h"

#include "HtmlReaderImpl.h"
#include "GlossaryHtmlParser.h"
#include "Exceptions/ConnectionFailed.h"

const std::string HtmlWordsCreatorImpl::urlAddress{"https://www.merriam-webster.com/dictionary/"};

HtmlWordsCreatorImpl::HtmlWordsCreatorImpl(std::unique_ptr<const HtmlReader> htmlReaderInit,
                                           std::unique_ptr<const HtmlParser> htmlParserInit)
        : htmlReader{std::move(htmlReaderInit)}, htmlParser{std::move(htmlParserInit)}
{
}

boost::optional<Word> HtmlWordsCreatorImpl::createWord(const WordWithTranslation& wordWithTranslation) const
{
    std::string htmlContent;
    try
    {
        htmlContent = htmlReader->read(urlAddress + wordWithTranslation.englishWord);
    }
    catch (const exceptions::ConnectionFailed& e)
    {
        std::cerr << e.what();
        return boost::none;
    }

    const auto parsedHtmlContent = htmlParser->parse(htmlContent);

    if (const auto wordDescription = wordDescriptionParser.parse(parsedHtmlContent))
    {
        return Word{wordWithTranslation.englishWord, wordWithTranslation.polishTranslation, *wordDescription};
    }
    return boost::none;
}

