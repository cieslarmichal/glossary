#include "DefaultDictionaryRepository.h"

namespace glossary::dictionary::repository
{
DefaultDictionaryRepository::DefaultDictionaryRepository(std::unique_ptr<DictionaryStorage> storageInit)
    : storage{std::move(storageInit)}

{
}

void DefaultDictionaryRepository::addDictionary(const std::string& dictionaryName)
{
    storage->addDictionary(dictionaryName);
}

void DefaultDictionaryRepository::addDictionary(const Dictionary& dictionary)
{
    storage->addDictionary(dictionary);
}

void DefaultDictionaryRepository::addWordToDictionary(const DictionaryWord& dictionaryWord,
                                                      const std::string& dictionaryName)
{
    storage->addWordToDictionary(dictionaryWord, dictionaryName);
}

void DefaultDictionaryRepository::removeDictionary(const std::string& dictionaryName)
{
    storage->removeDictionary(dictionaryName);
}

void DefaultDictionaryRepository::removeWordFromDictionary(const std::string& englishWord,
                                                           const std::string& dictionaryName)
{
    storage->removeWordFromDictionary(englishWord, dictionaryName);
}

void DefaultDictionaryRepository::changeWordTranslationFromDictionary(const std::string& englishWord,
                                                                      const std::string& translation,
                                                                      const std::string& dictionaryName)
{
    storage->changeWordTranslationFromDictionary(englishWord, translation, dictionaryName);
}

std::optional<Dictionary>
DefaultDictionaryRepository::getDictionary(const std::string& dictionaryName) const
{
    return storage->getDictionary(dictionaryName);
}

std::vector<Dictionary> DefaultDictionaryRepository::getDictionaries() const
{
    return storage->getDictionaries();
}

bool DefaultDictionaryRepository::containsDictionary(const std::string& dictionaryName) const
{
    return storage->containsDictionary(dictionaryName);
}

}