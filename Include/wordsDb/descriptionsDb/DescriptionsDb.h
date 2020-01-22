#pragma once

#include "WordDescription.h"
#include "boost/optional.hpp"

namespace wordsDb::descriptionsDb
{

class DescriptionsDb
{
public:
    virtual ~DescriptionsDb() = default;

    virtual void addWord(const WordDescription&) const = 0;
    virtual boost::optional<WordDescription> getWord(const EnglishWord&) const = 0;
    virtual bool contains(const EnglishWord&) const = 0;
};
}
