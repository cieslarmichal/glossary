#include "WordsBuilderImpl.h"

#include <iostream>

Words WordsBuilderImpl::buildWords(const translationsDb::Translations& translations,
                                   const wordsDescriptionsDb::WordsDescriptions& wordsDescriptions) const
{
    Words words;
    for (const auto& translation : translations)
    {
        const auto polishWord = translation.sourceText;
        const auto englishWord = translation.translatedText;
        words.push_back(
            {polishWord, englishWord, getCorrespondingWordDescription(englishWord, wordsDescriptions)});
    }
    return words;
}

wordsDescriptionsDb::WordDescription WordsBuilderImpl::getCorrespondingWordDescription(
    const wordsDescriptionsDb::EnglishWord& englishWord,
    const wordsDescriptionsDb::WordsDescriptions& wordsDescriptions) const
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
