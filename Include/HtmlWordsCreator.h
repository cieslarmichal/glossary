#pragma once

#include "wordsDb/translationsDb/Translation.h"
#include "wordsDb/wordsDescriptionsDb/WordDescription.h"

class HtmlWordsCreator
{
public:
    virtual ~HtmlWordsCreator() = default;

    virtual boost::optional<wordsDb::wordsDescriptionsDb::WordDescription>
    createWord(const wordsDb::translationsDb::Translation&) const = 0;
};