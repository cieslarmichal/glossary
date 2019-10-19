#pragma once

#include "Word.h"
#include "WordWithTranslation.h"

class HtmlWordsCreator
{
public:
    virtual ~HtmlWordsCreator() = default;

    virtual boost::optional<Word> createWord(const WordWithTranslation&) const = 0;
};