#pragma once

#include "boost/optional.hpp"
#include "wordsDb/descriptionsDb/WordsDescriptions.h"

namespace wordsDb::statisticsDb
{

class StatisticsStorage
{
public:
    virtual ~Storage() = default;

    virtual void addWord(const Word&) = 0;
    virtual boost::optional<Word> getWord(const EnglishWord&) const = 0;
    virtual Words getWords() const = 0;
    virtual bool contains(const EnglishWord&) const = 0;
    virtual Words::size_type size() const = 0;
    virtual bool empty() const = 0;
    virtual Words::const_iterator begin() const = 0;
    virtual Words::const_iterator end() const = 0;
};
}
