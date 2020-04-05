#include "DefaultDictionaryRepository.h"

namespace glossary::dictionaryService::repository
{
DefaultDictionaryRepository::DefaultDictionaryRepository(
    std::unique_ptr<DictionaryStorage> storageInit,
    std::unique_ptr<csvFileReading::DictionaryWordsReader> reader)
    : storage{std::move(storageInit)}, dictionaryWordsReader{std::move(reader)}

{
}

void DefaultDictionaryRepository::addDictionary(const DictionaryName& dictionaryName)
{
    storage->addDictionary(dictionaryName);
}

void DefaultDictionaryRepository::addDictionaryFromFile(const DictionaryName& dictionaryName,
                                                        const std::string& dictionaryWordsPath)
{
    const auto dictionaryWordsFromFile = dictionaryWordsReader->readDictionaryWords(dictionaryWordsPath);
    if (dictionaryWordsFromFile)
    {
        storage->addDictionary({dictionaryName, *dictionaryWordsFromFile});
    }
}

void DefaultDictionaryRepository::addWordToDictionary(const DictionaryWord& dictionaryWord,
                                                      const DictionaryName& dictionaryName)
{
    storage->addWordToDictionary(dictionaryWord, dictionaryName);
}

void DefaultDictionaryRepository::removeDictionary(const DictionaryName& dictionaryName)
{
    storage->removeDictionary(dictionaryName);
}

void DefaultDictionaryRepository::removeWordFromDictionary(const std::string& englishWord,
                                                           const DictionaryName& dictionaryName)
{
    storage->removeWordFromDictionary(englishWord, dictionaryName);
}

boost::optional<Dictionary>
DefaultDictionaryRepository::getDictionary(const DictionaryName& dictionaryName) const
{
    return storage->getDictionary(dictionaryName);
}

Dictionaries DefaultDictionaryRepository::getDictionaries() const
{
    return storage->getDictionaries();
}

bool DefaultDictionaryRepository::containsDictionary(const DictionaryName& dictionaryName) const
{
    return storage->containsDictionary(dictionaryName);
}

}