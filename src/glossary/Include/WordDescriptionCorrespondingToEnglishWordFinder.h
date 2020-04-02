#pragma once

#include "boost/optional.hpp"

#include "wordDescriptionRepository/WordDescription.h"

namespace glossary
{
class WordDescriptionCorrespondingToEnglishWordFinder
{
public:
    boost::optional<wordDescriptionRepository::WordDescription>
    findCorrespondingWordDescription(const wordDescriptionRepository::EnglishWord&,
                                     const wordDescriptionRepository::WordsDescriptions&) const;
};
}