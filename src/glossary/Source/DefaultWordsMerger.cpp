#include "DefaultWordsMerger.h"

UniqueWords
DefaultWordsMerger::mergeWords(const dictionaryRepository::DictionaryWords& dictionaryWords,
                               const wordDescriptionRepository::WordsDescriptions& wordsDescriptions) const
{
    UniqueWords mergedWords;
    for (const auto& dictionaryWord : dictionaryWords)
    {
        const auto englishWord = dictionaryWord.englishWord;
        const auto polishWord = dictionaryWord.translation;
        const auto wordDescription = getCorrespondingWordDescription(englishWord, wordsDescriptions);
        mergedWords.emplace_back(getCreatedWord(englishWord, polishWord, wordDescription));
    }
    return mergedWords;
}

boost::optional<wordDescriptionRepository::WordDescription>
DefaultWordsMerger::getCorrespondingWordDescription(
    const wordDescriptionRepository::EnglishWord& englishWord,
    const wordDescriptionRepository::WordsDescriptions& wordsDescriptions) const
{
    return wordDescriptionFinder.findCorrespondingWordDescription(englishWord, wordsDescriptions);
}

std::unique_ptr<Word> DefaultWordsMerger::getCreatedWord(
    const wordDescriptionRepository::EnglishWord& englishWord,
    const boost::optional<PolishWord>& polishTranslation,
    const boost::optional<wordDescriptionRepository::WordDescription>& wordDescription) const
{
    return wordCreator.create(englishWord, polishTranslation, wordDescription);
}
