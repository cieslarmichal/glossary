#pragma once

#include "Word.h"
#include "boost/optional.hpp"

class Database
{
public:
    virtual ~Database() = default;

    virtual void addWord(const Word&) const = 0;
    virtual boost::optional<Word> getWord(const EnglishWord&) const = 0;
    virtual bool contains(const EnglishWord&) const = 0;
};
