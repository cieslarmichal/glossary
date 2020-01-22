#include <iostream>

#include "wordsDb/descriptionsDb/DescriptionsMemoryStorage.h"

namespace wordsDb::descriptionsDb
{
void DescriptionsMemoryStorage::addWord(const WordDescription& word)
{
    if (not contains(word.englishWord))
    {
        words.push_back(word);
    }
}

boost::optional<WordDescription>
DescriptionsMemoryStorage::getWord(const EnglishWord& englishWord) const
{
    const auto word = std::find_if(words.begin(), words.end(),
                                   [englishWord](const WordDescription& word) {
                                       return word.englishWord == englishWord;
                                   });

    if (word != words.end())
    {
        return *word;
    }
    return boost::none;
}

Words DescriptionsMemoryStorage::getWords() const
{
    return words;
}

bool DescriptionsMemoryStorage::contains(const EnglishWord& wordToFind) const
{
    const auto found = std::find_if(words.begin(), words.end(),
                                    [wordToFind](const WordDescription& word) {
                                        return word.englishWord == wordToFind;
                                    });
    return found != words.end();
}

Words::size_type DescriptionsMemoryStorage::size() const
{
    return words.size();
}

bool DescriptionsMemoryStorage::empty() const
{
    return words.empty();
}

Words::const_iterator DescriptionsMemoryStorage::begin() const
{
    return words.cbegin();
}

Words::const_iterator DescriptionsMemoryStorage::end() const
{
    return words.cend();
}
}

