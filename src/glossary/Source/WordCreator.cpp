#include "WordCreator.h"

std::unique_ptr<Word> WordCreator::create(
    const PolishWord& polishWord, const wordDescriptionRepository::EnglishWord& englishWord,
    const boost::optional<wordDescriptionRepository::WordDescription>& wordDescriptionOpt) const
{
    return std::make_unique<Word>(polishWord, englishWord, wordDescriptionOpt);
}
