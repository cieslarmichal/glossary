#include "WordsDatabase.h"

WordsDatabase::WordsDatabase(std::unique_ptr<Storage> storageInit) : storage{std::move(storageInit)}
{
}

void WordsDatabase::addWord(const Word& word) const
{
    storage->addWord(word);
}

boost::optional<Word> WordsDatabase::getWord(const EnglishWord& englishWord) const
{
    return storage->getWord(englishWord);
}

bool WordsDatabase::contains(const EnglishWord& englishWord) const
{
    return storage->contains(englishWord);
}

