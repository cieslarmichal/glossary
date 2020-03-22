#include "DefaultWordsMerger.h"

UniqueWords DefaultWordsMerger::mergeWords(
    const translationRepository::Translations& translations,
    const wordDescriptionRepository::WordsDescriptions& wordsDescriptions) const
{
    UniqueWords mergedWords;
    for (const auto& translation : translations)
    {
        const auto polishWord = translation.sourceText;
        const auto englishWord = translation.translatedText;
        auto wordDescription = getCorrespondingWordDescription(englishWord, wordsDescriptions);
        mergedWords.emplace_back(getCreatedWord(polishWord, englishWord, wordDescription));
    }
    return mergedWords;
}

boost::optional<wordDescriptionRepository::WordDescription> DefaultWordsMerger::getCorrespondingWordDescription(
    const wordDescriptionRepository::EnglishWord& englishWord,
    const wordDescriptionRepository::WordsDescriptions& wordsDescriptions) const
{
    return wordDescriptionFinder.find(englishWord, wordsDescriptions);
}

std::unique_ptr<Word>
DefaultWordsMerger::getCreatedWord(const PolishWord& polishWord, const wordDescriptionRepository::EnglishWord& englishWord,
                                   boost::optional<wordDescriptionRepository::WordDescription>& wordDescription) const
{
    return wordCreator.create(polishWord, englishWord, wordDescription);
}
