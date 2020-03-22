#pragma once

#include "WordsBuilder.h"

class DefaultWordsBuilder : public WordsBuilder
{
public:
    Words buildWords(const translationRepository::Translations&,
                     const wordDescriptionRepository::WordsDescriptions&) const override;

private:
    wordDescriptionRepository::WordDescription
    getCorrespondingWordDescription(const wordDescriptionRepository::EnglishWord&,
                                    const wordDescriptionRepository::WordsDescriptions&) const;
};