#pragma once

#include "WordsDescriptions.h"
#include "boost/optional.hpp"

namespace wordsDb::descriptionsDb
{

class DescriptionsDb
{
public:
    virtual ~DescriptionsDb() = default;

    virtual void addWordDescription(const WordDescription&) const = 0;
    virtual boost::optional<WordDescription>
    getWordDescription(const EnglishWord&) const = 0;
    virtual WordsDescriptions getWordsDescriptions() const = 0;
    virtual bool contains(const EnglishWord&) const = 0;
};
}
