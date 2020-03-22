#pragma once

#include "WordDescriptionFinder.h"
#include "WordsMerger.h"
#include "WordCreator.h"

class DefaultWordsMerger : public WordsMerger
{
public:
    UniqueWords mergeWords(const translationRepository::Translations&,
                     const wordDescriptionRepository::WordsDescriptions&) const override;

private:
    boost::optional<wordDescriptionRepository::WordDescription>
    getCorrespondingWordDescription(const wordDescriptionRepository::EnglishWord&,
                                    const wordDescriptionRepository::WordsDescriptions&) const;
    std::unique_ptr<Word>
    getCreatedWord(const PolishWord&, const wordDescriptionRepository::EnglishWord&,
                                    boost::optional<wordDescriptionRepository::WordDescription>&) const;

    WordDescriptionFinder wordDescriptionFinder;
    WordCreator wordCreator;
};