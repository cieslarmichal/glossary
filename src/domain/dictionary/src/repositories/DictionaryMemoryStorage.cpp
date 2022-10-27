#include "DictionaryMemoryStorage.h"

namespace glossary::dictionary
{
static auto& getDictionaryByPosition(std::vector<Dictionary>& dictionaries,
                                     std::vector<Dictionary>::const_iterator position)
{
    const auto distance = std::vector<Dictionary>::size_type(std::distance(dictionaries.cbegin(), position));
    return dictionaries.at(distance);
}

static auto& getDictionaryByPosition(const std::vector<Dictionary>& dictionaries,
                                     std::vector<Dictionary>::const_iterator position)
{
    const auto distance = std::vector<Dictionary>::size_type(std::distance(dictionaries.cbegin(), position));
    return dictionaries.at(distance);
}

static auto& getDictionaryWordByPosition(std::vector<DictionaryWord>& dictionaryWords,
                                         std::vector<DictionaryWord>::const_iterator position)
{
    const auto distance = std::vector<DictionaryWord>::size_type(std::distance(dictionaryWords.cbegin(), position));
    return dictionaryWords.at(distance);
}

void DictionaryMemoryStorage::addDictionary(const std::string& dictionaryName)
{
    if (not dictionaryExists(dictionaryName))
        dictionaries.push_back(Dictionary{dictionaryName, std::vector<DictionaryWord>{}});
}

void DictionaryMemoryStorage::addDictionary(const Dictionary& dictionary)
{
    if (not dictionaryExists(dictionary.name))
        dictionaries.emplace_back(dictionary);
}

void DictionaryMemoryStorage::addWordToDictionary(const DictionaryWord& dictionaryWord,
                                                  const std::string& dictionaryName)
{
    if (dictionaryExists(dictionaryName) &&
        englishWordNotExistsInDictionary(dictionaryWord.englishWord, dictionaryName))
    {
        auto& dictionary = getDictionaryByPosition(dictionaries, findDictionaryPosition(dictionaryName));
        dictionary.words.emplace_back(dictionaryWord);
    }
}

void DictionaryMemoryStorage::removeDictionary(const std::string& dictionaryName)
{
    if (dictionaryExists(dictionaryName))
        dictionaries.erase(findDictionaryPosition(dictionaryName));
}

void DictionaryMemoryStorage::removeWordFromDictionary(const std::string& englishWord,
                                                       const std::string& dictionaryName)
{
    if (dictionaryExists(dictionaryName) && englishWordExistsInDictionary(englishWord, dictionaryName))
    {
        auto& dictionary = getDictionaryByPosition(dictionaries, findDictionaryPosition(dictionaryName));
        dictionary.words.erase(findWordInsideDictionaryPosition(englishWord, dictionary));
    }
}

void DictionaryMemoryStorage::changeWordTranslationFromDictionary(const std::string& englishWord,
                                                                  const std::string& translation,
                                                                  const std::string& dictionaryName)
{
    if (dictionaryExists(dictionaryName) && englishWordExistsInDictionary(englishWord, dictionaryName))
    {
        auto& dictionary = getDictionaryByPosition(dictionaries, findDictionaryPosition(dictionaryName));
        auto& dictionaryWord =
            getDictionaryWordByPosition(dictionary.words, findWordInsideDictionaryPosition(englishWord, dictionary));
        dictionaryWord.translation = translation;
    }
}

std::optional<Dictionary> DictionaryMemoryStorage::getDictionary(const std::string& dictionaryName) const
{
    auto dictionaryPosition = findDictionaryPosition(dictionaryName);
    if (dictionaryPosition != dictionaries.end())
        return getDictionaryByPosition(dictionaries, dictionaryPosition);
    return std::nullopt;
}

std::vector<Dictionary> DictionaryMemoryStorage::getDictionaries() const
{
    return dictionaries;
}

bool DictionaryMemoryStorage::containsDictionary(const std::string& dictionaryName) const
{
    return findDictionaryPosition(dictionaryName) != dictionaries.end();
}

std::vector<Dictionary>::size_type DictionaryMemoryStorage::size() const
{
    return dictionaries.size();
}

bool DictionaryMemoryStorage::empty() const
{
    return dictionaries.empty();
}

std::vector<Dictionary>::const_iterator
DictionaryMemoryStorage::findDictionaryPosition(const std::string& dictionaryNameToFind) const
{
    return std::find_if(dictionaries.begin(), dictionaries.end(),
                        [&dictionaryNameToFind](const Dictionary& dictionary)
                        { return dictionary.name == dictionaryNameToFind; });
}

std::vector<DictionaryWord>::const_iterator
DictionaryMemoryStorage::findWordInsideDictionaryPosition(const std::string& englishWordToFind,
                                                          const Dictionary& dictionary) const
{
    return std::find_if(dictionary.words.begin(), dictionary.words.end(),
                        [&englishWordToFind](const DictionaryWord& dictionaryWord)
                        { return dictionaryWord.englishWord == englishWordToFind; });
}

bool DictionaryMemoryStorage::dictionaryExists(const std::string& dictionaryName) const
{
    return containsDictionary(dictionaryName);
}

bool DictionaryMemoryStorage::englishWordExistsInDictionary(const std::string& englishWord,
                                                            const std::string& dictionaryName) const
{
    if (dictionaryExists(dictionaryName))
    {
        auto& dictionary = getDictionaryByPosition(dictionaries, findDictionaryPosition(dictionaryName));
        return findWordInsideDictionaryPosition(englishWord, dictionary) != dictionary.words.end();
    }
    return false;
}

bool DictionaryMemoryStorage::englishWordNotExistsInDictionary(const std::string& englishWord,
                                                               const std::string& dictionaryName) const
{
    return not englishWordExistsInDictionary(englishWord, dictionaryName);
}

}
