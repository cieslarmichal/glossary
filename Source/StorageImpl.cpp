#include "StorageImpl.h"

StorageImpl::StorageImpl(const std::vector<Word>& wordsInit) : words{wordsInit}
{
}

void StorageImpl::addWord(const Word& word)
{
    if(not wordExists(word))
    {
       words.push_back(word);
    }
}

boost::optional<Word> StorageImpl::getWord(const EnglishWord& englishWord) const
{
    auto word = std::find_if(words.begin(), words.end(), [englishWord](const Word& word)
    { return word.englishWord == englishWord; });

    if (word != words.end())
    {
        return *word;
    }
    return boost::none;
}

Words StorageImpl::getWords() const
{
    return words;
}

Words::size_type StorageImpl::size() const
{
    return words.size();
}

bool StorageImpl::empty() const
{
    return words.empty();
}

Words::const_iterator StorageImpl::begin() const
{
    return words.cbegin();
}

Words::const_iterator StorageImpl::end() const
{
    return words.cend();
}

bool StorageImpl::wordExists(const Word& wordToFind) const
{
    auto word = std::find(words.begin(), words.begin(), wordToFind);

    return word != words.end();
}

