#pragma once

#include "WordsBuilder.h"

class WordsBuilderImpl : public WordsBuilder
{
public:
    Words buildWords(const translationsDb::Translations&,
                     const wordsDescriptionsDb::WordsDescriptions&) const override;

private:
    wordsDescriptionsDb::WordDescription
    getCorrespondingWordDescription(const wordsDescriptionsDb::EnglishWord&,
                                    const wordsDescriptionsDb::WordsDescriptions&) const;
};