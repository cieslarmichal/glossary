#pragma once

#include "wordDescriptionRepository/WordDescription.h"
#include "boost/optional.hpp"

class WordDescriptionFinder
{
public:
    boost::optional<wordDescriptionRepository::WordDescription>
    find(const wordDescriptionRepository::EnglishWord&,
         const wordDescriptionRepository::WordsDescriptions&) const;
};