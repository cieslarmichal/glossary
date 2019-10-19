#pragma once

#include "HtmlWordsCreator.h"
#include "HtmlReader.h"
#include "HtmlParser.h"
#include "WordDescriptionParser.h"
#include <memory>

class HtmlWordsCreatorImpl : public HtmlWordsCreator
{
public:
    explicit HtmlWordsCreatorImpl(std::unique_ptr<const HtmlReader>, std::unique_ptr<const HtmlParser>);

    boost::optional<Word> createWord(const WordWithTranslation&) const override;

private:
    std::unique_ptr<const HtmlReader> htmlReader;
    std::unique_ptr<const HtmlParser> htmlParser;
    WordDescriptionParser wordDescriptionParser;

    static const std::string urlAddress;
};