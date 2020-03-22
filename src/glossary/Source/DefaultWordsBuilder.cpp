#include "DefaultWordsBuilder.h"

Words DefaultWordsBuilder::buildWords(
    const translationRepository::Translations& translations,
    const wordDescriptionRepository::WordsDescriptions& wordsDescriptions) const
{
    Words builtWords;
    for (const auto& translation : translations)
    {
        const auto polishWord = translation.sourceText;
        const auto englishWord = translation.translatedText;
        const auto word =
            Word{polishWord, englishWord, getCorrespondingWordDescription(englishWord, wordsDescriptions)};
        builtWords.emplace_back(word);
    }
    return builtWords;
}

wordDescriptionRepository::WordDescription DefaultWordsBuilder::getCorrespondingWordDescription(
    const wordDescriptionRepository::EnglishWord& englishWord,
    const wordDescriptionRepository::WordsDescriptions& wordsDescriptions) const
{
    for (const auto& wordDescription : wordsDescriptions)
    {
        if (wordDescription.englishWord == englishWord)
        {
            return wordDescription;
        }
    }
    return {englishWord, {}};
}
