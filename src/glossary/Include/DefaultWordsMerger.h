#pragma once

#include "WordCreator.h"
#include "WordDescriptionCorrespondingToEnglishWordFinder.h"
#include "WordsMerger.h"

class DefaultWordsMerger : public WordsMerger
{
public:
    UniqueWords mergeWords(const dictionaryRepository::DictionaryWords&,
                           const wordDescriptionRepository::WordsDescriptions&) const override;

private:
    boost::optional<wordDescriptionRepository::WordDescription>
    getCorrespondingWordDescription(const wordDescriptionRepository::EnglishWord&,
                                    const wordDescriptionRepository::WordsDescriptions&) const;
    std::unique_ptr<Word>
    getCreatedWord(const wordDescriptionRepository::EnglishWord&, const boost::optional<PolishWord>&,
                   const boost::optional<wordDescriptionRepository::WordDescription>&) const;

    WordDescriptionCorrespondingToEnglishWordFinder wordDescriptionFinder;
    WordCreator wordCreator;
};