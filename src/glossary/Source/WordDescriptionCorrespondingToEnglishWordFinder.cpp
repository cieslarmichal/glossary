#include "WordDescriptionCorrespondingToEnglishWordFinder.h"

boost::optional<wordDescriptionRepository::WordDescription>
WordDescriptionCorrespondingToEnglishWordFinder::findCorrespondingWordDescription(
    const wordDescriptionRepository::EnglishWord& englishWordToFind,
    const wordDescriptionRepository::WordsDescriptions& wordsDescriptions) const
{
    for (const auto& wordDescription : wordsDescriptions)
    {
        if (wordDescription.englishWord == englishWordToFind)
        {
            return wordDescription;
        }
    }
    return boost::none;
}
