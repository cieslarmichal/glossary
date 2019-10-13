#pragma once
#include "Word.h"
#include "WordWithTranslation.h"

class HtmlWordsCreator
{
public:
    virtual ~HtmlWordsCreator() = default;

    virtual Word createWord(const WordWithTranslation&) const = 0;
};