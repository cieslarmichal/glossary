#pragma once

#include "boost/optional.hpp"

#include "WordDescription.h"

namespace wordDescriptionRepository
{
class WordsDescriptionsStorage
{
public:
    virtual ~WordsDescriptionsStorage() = default;

    virtual void addWordDescription(const WordDescription&) = 0;
    virtual boost::optional<WordDescription> getWordDescription(const EnglishWord&) const = 0;
    virtual WordsDescriptions getWordsDescriptions() const = 0;
    virtual bool contains(const EnglishWord&) const = 0;
    virtual WordsDescriptions::size_type size() const = 0;
    virtual bool empty() const = 0;
    virtual WordsDescriptions::const_iterator begin() const = 0;
    virtual WordsDescriptions::const_iterator end() const = 0;
};
}
