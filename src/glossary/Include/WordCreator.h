#pragma once

#include "boost/optional.hpp"

#include "Word.h"
#include <memory>

class WordCreator
{
public:
    std::unique_ptr<Word> create(const PolishWord&, const wordDescriptionRepository::EnglishWord&,
                const boost::optional<wordDescriptionRepository::WordDescription>&) const;
};