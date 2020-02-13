#include "wordsDescriptionsDb/WordsDescriptionsMemoryStorage.h"

namespace wordsDescriptionsDb
{
void WordsDescriptionsMemoryStorage::addWordDescription(
    const WordDescription& wordDescription)
{
    if (not contains(wordDescription.englishWord))
    {
        wordsDescriptions.push_back(wordDescription);
    }
}

boost::optional<WordDescription>
WordsDescriptionsMemoryStorage::getWordDescription(
    const EnglishWord& englishWord) const
{
    const auto wordDescriptionIter = getWordsDescriptionsIter(englishWord);

    if (wordDescriptionIter != wordsDescriptions.end())
    {
        return *wordDescriptionIter;
    }
    return boost::none;
}

WordsDescriptions WordsDescriptionsMemoryStorage::getWordsDescriptions() const
{
    return wordsDescriptions;
}

bool WordsDescriptionsMemoryStorage::contains(
    const EnglishWord& wordToFind) const
{
    return getWordsDescriptionsIter(wordToFind) != wordsDescriptions.end();
}

WordsDescriptions::size_type WordsDescriptionsMemoryStorage::size() const
{
    return wordsDescriptions.size();
}

bool WordsDescriptionsMemoryStorage::empty() const
{
    return wordsDescriptions.empty();
}

WordsDescriptions::const_iterator WordsDescriptionsMemoryStorage::begin() const
{
    return wordsDescriptions.cbegin();
}

WordsDescriptions::const_iterator WordsDescriptionsMemoryStorage::end() const
{
    return wordsDescriptions.cend();
}

WordsDescriptions::const_iterator
WordsDescriptionsMemoryStorage::getWordsDescriptionsIter(
    const EnglishWord& wordToFind) const
{
    return std::find_if(wordsDescriptions.begin(), wordsDescriptions.end(),
                        [wordToFind](const WordDescription& wordDescription) {
                            return wordDescription.englishWord == wordToFind;
                        });
}

}
