#pragma once

#include "wordsDb/descriptionsDb/WordDescription.h"
#include "wordsDb/translationsDb/Translation.h"

class HtmlWordsCreator
{
public:
    virtual ~HtmlWordsCreator() = default;

    virtual boost::optional<wordsDb::descriptionsDb::WordDescription>
    createWord(const wordsDb::translationsDb::Translation&) const = 0;
};