#include "DictionaryMemoryStorage.h"

namespace glossary::dictionaryService::repository
{
static auto& getDictionaryByPosition(Dictionaries& dictionaries, Dictionaries::const_iterator position)
{
    const auto distance = Dictionaries::size_type(std::distance(dictionaries.cbegin(), position));
    return dictionaries.at(distance);
}

static auto& getDictionaryByPosition(const Dictionaries& dictionaries, Dictionaries::const_iterator position)
{
    const auto distance = Dictionaries::size_type(std::distance(dictionaries.cbegin(), position));
    return dictionaries.at(distance);
}

void DictionaryMemoryStorage::addDictionary(const DictionaryName& dictionaryName)
{
    if (not dictionaryExists(dictionaryName))
        dictionaries.push_back(Dictionary{dictionaryName, DictionaryWords{}});
}

void DictionaryMemoryStorage::addDictionary(const Dictionary& dictionary)
{
    if (not dictionaryExists(dictionary.name))
        dictionaries.emplace_back(dictionary);
}

void DictionaryMemoryStorage::addWordToDictionary(const DictionaryWord& dictionaryWord,
                                                  const DictionaryName& dictionaryName)
{
    if (dictionaryExists(dictionaryName) &&
        englishWordNotExistsInDictionary(dictionaryWord.englishWord, dictionaryName))
    {
        auto& dictionary = getDictionaryByPosition(dictionaries, findDictionaryPosition(dictionaryName));
        dictionary.words.emplace_back(dictionaryWord);
    }
}

void DictionaryMemoryStorage::removeDictionary(const DictionaryName& dictionaryName)
{
    if (dictionaryExists(dictionaryName))
        dictionaries.erase(findDictionaryPosition(dictionaryName));
}

void DictionaryMemoryStorage::removeWordFromDictionary(const std::string& englishWord,
                                                       const DictionaryName& dictionaryName)
{
    if (dictionaryExists(dictionaryName) && englishWordExistsInDictionary(englishWord, dictionaryName))
    {
        auto& dictionary = getDictionaryByPosition(dictionaries, findDictionaryPosition(dictionaryName));
        dictionary.words.erase(findWordInsideDictionaryPosition(englishWord, dictionary));
    }
}

boost::optional<Dictionary> DictionaryMemoryStorage::getDictionary(const DictionaryName& dictionaryName) const
{
    auto dictionaryPosition = findDictionaryPosition(dictionaryName);
    if (dictionaryPosition != dictionaries.end())
        return getDictionaryByPosition(dictionaries, dictionaryPosition);
    return boost::none;
}

Dictionaries DictionaryMemoryStorage::getDictionaries() const
{
    return dictionaries;
}

bool DictionaryMemoryStorage::containsDictionary(const DictionaryName& dictionaryName) const
{
    return findDictionaryPosition(dictionaryName) != dictionaries.end();
}

Dictionaries::size_type DictionaryMemoryStorage::size() const
{
    return dictionaries.size();
}

bool DictionaryMemoryStorage::empty() const
{
    return dictionaries.empty();
}

Dictionaries::const_iterator
DictionaryMemoryStorage::findDictionaryPosition(const DictionaryName& dictionaryNameToFind) const
{
    return std::find_if(dictionaries.begin(), dictionaries.end(),
                        [&dictionaryNameToFind](const Dictionary& dictionary) {
                            return dictionary.name == dictionaryNameToFind;
                        });
}

DictionaryWords::const_iterator
DictionaryMemoryStorage::findWordInsideDictionaryPosition(const std::string& englishWordToFind,
                                                          const Dictionary& dictionary) const
{
    return std::find_if(dictionary.words.begin(), dictionary.words.end(),
                        [&englishWordToFind](const DictionaryWord& dictionaryWord) {
                            return dictionaryWord.englishWord == englishWordToFind;
                        });
}

bool DictionaryMemoryStorage::dictionaryExists(const DictionaryName& dictionaryName) const
{
    return containsDictionary(dictionaryName);
}

bool DictionaryMemoryStorage::englishWordExistsInDictionary(const EnglishWord& englishWord,
                                                            const DictionaryName& dictionaryName) const
{
    if (dictionaryExists(dictionaryName))
    {
        auto& dictionary = getDictionaryByPosition(dictionaries, findDictionaryPosition(dictionaryName));
        return findWordInsideDictionaryPosition(englishWord, dictionary) != dictionary.words.end();
    }
    return false;
}

bool DictionaryMemoryStorage::englishWordNotExistsInDictionary(const std::string& englishWord,
                                                               const DictionaryName& dictionaryName) const
{
    return not englishWordExistsInDictionary(englishWord, dictionaryName);
}

}
