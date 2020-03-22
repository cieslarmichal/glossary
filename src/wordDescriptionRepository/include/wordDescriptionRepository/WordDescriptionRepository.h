#pragma once

#include "boost/optional.hpp"

#include "WordDescription.h"

namespace wordDescriptionRepository
{

class WordDescriptionRepository
{
public:
    virtual ~WordDescriptionRepository() = default;

    virtual void addWordDescription(const WordDescription&) = 0;
    virtual boost::optional<WordDescription> getWordDescription(const EnglishWord&) const = 0;
    virtual bool contains(const EnglishWord&) const = 0;
};
}
