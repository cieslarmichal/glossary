#include "DefaultDictionaryRepository.h"

namespace glossary::dictionaryService::repository
{
DefaultDictionaryRepository::DefaultDictionaryRepository(std::unique_ptr<DictionaryStorage> storageInit)
    : storage{std::move(storageInit)}

{
}

void DefaultDictionaryRepository::addDictionary(const DictionaryName& dictionaryName)
{
    storage->addDictionary(dictionaryName);
}

void DefaultDictionaryRepository::addDictionary(const Dictionary& dictionary)
{
    storage->addDictionary(dictionary);
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

void DefaultDictionaryRepository::removeWordFromDictionary(const EnglishWord& englishWord,
                                                           const DictionaryName& dictionaryName)
{
    storage->removeWordFromDictionary(englishWord, dictionaryName);
}

void DefaultDictionaryRepository::changeWordTranslationFromDictionary(const EnglishWord& englishWord, const std::string& translation,
                                                                      const DictionaryName& dictionaryName)
{
    storage->changeWordTranslationFromDictionary(englishWord, translation, dictionaryName);
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