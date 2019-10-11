#include <iostream>
#include "MemoryStorage.h"

void MemoryStorage::addWord(const Word& word)
{
    if(not contains(word))
    {
       words.push_back(word);
    }
}

boost::optional<Word> MemoryStorage::getWord(const EnglishWord& englishWord) const
{
    auto word = std::find_if(words.begin(), words.end(), [englishWord](const Word& word)
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

bool MemoryStorage::contains(const Word& wordToFind) const
{
    if(std::find(words.begin(), words.end(), wordToFind) != words.end())
    {
        //syslog
        return true;
    }
    return false;
}

