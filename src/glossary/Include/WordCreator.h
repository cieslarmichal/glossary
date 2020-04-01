#pragma once

#include <memory>

#include "boost/optional.hpp"

#include "Word.h"

class WordCreator
{
public:
    std::unique_ptr<Word> create(const wordDescriptionRepository::EnglishWord&,
                                 const boost::optional<PolishWord>&,
                                 const boost::optional<wordDescriptionRepository::WordDescription>&) const;
};