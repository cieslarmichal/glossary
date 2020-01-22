#pragma once

#include "WordsDescriptions.h"
#include "boost/optional.hpp"

namespace wordsDb::descriptionsDb
{

class DescriptionsStorage
{
public:
    virtual ~DescriptionsStorage() = default;

    virtual void addWord(const WordDescription&) = 0;
    virtual boost::optional<WordDescription> getWord(const EnglishWord&) const = 0;
    virtual Words getWords() const = 0;
    virtual bool contains(const EnglishWord&) const = 0;
    virtual Words::size_type size() const = 0;
    virtual bool empty() const = 0;
    virtual Words::const_iterator begin() const = 0;
    virtual Words::const_iterator end() const = 0;
};
}
