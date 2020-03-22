#pragma once

#include "WordsBuilder.h"

class DefaultWordsBuilder : public WordsBuilder
{
public:
    Words buildWords(const translationsDb::Translations&,
                     const wordDescriptionRepository::WordsDescriptions&) const override;

private:
    wordDescriptionRepository::WordDescription
    getCorrespondingWordDescription(const wordDescriptionRepository::EnglishWord&,
                                    const wordDescriptionRepository::WordsDescriptions&) const;
};