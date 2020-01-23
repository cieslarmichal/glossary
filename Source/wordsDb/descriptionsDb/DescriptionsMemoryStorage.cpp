#include "wordsDb/descriptionsDb/DescriptionsMemoryStorage.h"

#include <iostream>

namespace wordsDb::descriptionsDb
{
void DescriptionsMemoryStorage::addWordDescription(const WordDescription& word)
{
    if (not contains(word.englishWord))
    {
        words.push_back(word);
    }
}

boost::optional<WordDescription> DescriptionsMemoryStorage::getWordDescription(
    const EnglishWord& englishWord) const
{
    const auto word = getWordIter(englishWord);

    if (word != words.end())
    {
        return *word;
    }
    return boost::none;
}

WordsDescriptions DescriptionsMemoryStorage::getWordsDescriptions() const
{
    return words;
}

bool DescriptionsMemoryStorage::contains(const EnglishWord& wordToFind) const
{
    return getWordIter(wordToFind) != words.end();
}

WordsDescriptions::size_type DescriptionsMemoryStorage::size() const
{
    return words.size();
}

bool DescriptionsMemoryStorage::empty() const
{
    return words.empty();
}

WordsDescriptions::const_iterator DescriptionsMemoryStorage::begin() const
{
    return words.cbegin();
}

WordsDescriptions::const_iterator DescriptionsMemoryStorage::end() const
{
    return words.cend();
}

WordsDescriptions::const_iterator
DescriptionsMemoryStorage::getWordIter(const EnglishWord& wordToFind) const
{
    return std::find_if(words.begin(), words.end(),
                        [wordToFind](const WordDescription& wordDescription) {
                            return wordDescription.englishWord == wordToFind;
                        });
}

}
