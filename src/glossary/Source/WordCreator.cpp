#include "WordCreator.h"

namespace glossary
{
std::unique_ptr<Word> WordCreator::create(
    const wordDescriptionRepository::EnglishWord& englishWord,
    const boost::optional<PolishWord>& polishWordOpt,
    const boost::optional<wordDescriptionRepository::WordDescription>& wordDescriptionOpt) const
{
    return std::make_unique<Word>(englishWord, polishWordOpt, wordDescriptionOpt);
}
}