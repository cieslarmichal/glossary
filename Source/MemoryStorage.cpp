#include <iostream>
#include "MemoryStorage.h"

void MemoryStorage::addWord(const Word& word)
{
    if(not contains(word.englishWord))
    {
       words.push_back(word);
    }
}

boost::optional<Word> MemoryStorage::getWord(const EnglishWord& englishWord) const
{
    const auto word = std::find_if(words.begin(), words.end(), [englishWord](const Word& word)
    { return word.englishWord == englishWord; });

    if (word != words.end())
    {
        return *word;
    }
    return boost::none;
}

Words MemoryStorage::getWords() const
{
    return words;
}

bool MemoryStorage::contains(const EnglishWord& wordToFind) const
{
    const auto found = std::find_if(
            words.begin(), words.end(),
            [wordToFind](const Word& word) { return word.englishWord == wordToFind;});
    return found != words.end();
}

Words::size_type MemoryStorage::size() const
{
    return words.size();
}

bool MemoryStorage::empty() const
{
    return words.empty();
}

Words::const_iterator MemoryStorage::begin() const
{
    return words.cbegin();
}

Words::const_iterator MemoryStorage::end() const
{
    return words.cend();
}

