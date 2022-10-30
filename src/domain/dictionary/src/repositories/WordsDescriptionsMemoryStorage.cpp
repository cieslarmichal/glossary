#include "WordsDescriptionsMemoryStorage.h"

namespace glossary::dictionary
{
void WordsDescriptionsMemoryStorage::addWordDescription(const WordDescription& wordDescription)
{
    if (not contains(wordDescription.englishWord))
    {
        wordsDescriptions.push_back(wordDescription);
    }
}

std::optional<WordDescription> WordsDescriptionsMemoryStorage::getWordDescription(const std::string& englishWord) const
{
    const auto wordDescriptionIter = getWordsDescriptionsIter(englishWord);

    if (wordDescriptionIter != wordsDescriptions.end())
    {
        return *wordDescriptionIter;
    }
    return std::nullopt;
}

std::vector<WordDescription> WordsDescriptionsMemoryStorage::getWordsDescriptions() const
{
    return wordsDescriptions;
}

bool WordsDescriptionsMemoryStorage::contains(const std::string& wordToFind) const
{
    return getWordsDescriptionsIter(wordToFind) != wordsDescriptions.end();
}

std::vector<WordDescription>::size_type WordsDescriptionsMemoryStorage::size() const
{
    return wordsDescriptions.size();
}

bool WordsDescriptionsMemoryStorage::empty() const
{
    return wordsDescriptions.empty();
}

std::vector<WordDescription>::const_iterator
WordsDescriptionsMemoryStorage::getWordsDescriptionsIter(const std::string& wordToFind) const
{
    return std::find_if(wordsDescriptions.begin(), wordsDescriptions.end(),
                        [wordToFind](const WordDescription& wordDescription)
                        { return wordDescription.englishWord == wordToFind; });
}

}
