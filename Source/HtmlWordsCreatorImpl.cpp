#include "HtmlWordsCreatorImpl.h"
#include <iostream>

#include "HtmlReaderImpl.h"
#include "GlossaryHtmlParser.h"

const std::string HtmlWordsCreatorImpl::urlAddress{"https://www.merriam-webster.com/dictionary/"};

HtmlWordsCreatorImpl::HtmlWordsCreatorImpl(std::unique_ptr<const HtmlReader> htmlReaderInit,
                                           std::unique_ptr<const HtmlParser> htmlParserInit)
        : htmlReader{std::move(htmlReaderInit)}, htmlParser{std::move(htmlParserInit)}
{
}

Word HtmlWordsCreatorImpl::createWord(const WordWithTranslation& wordWithTranslation) const
{
    auto htmlContent = htmlReader->read(urlAddress + wordWithTranslation.englishWord);
    auto parsedHtmlContent = htmlParser->parse(htmlContent);
    auto wordDescription = wordDescriptionParser.parse(parsedHtmlContent);
    return Word{wordWithTranslation.englishWord, wordWithTranslation.polishTranslation, wordDescription};
}

