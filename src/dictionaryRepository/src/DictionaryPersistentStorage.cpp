#include "DictionaryPersistentStorage.h"

#include <iostream>

#include "utils/GetProjectPath.h"

namespace glossary::dictionaryRepository
{
const std::string DictionaryPersistentStorage::directory{utils::getProjectPath("glossary") + "database/"};
const std::string DictionaryPersistentStorage::filename{directory + "dictionaries.txt"};

DictionaryPersistentStorage::DictionaryPersistentStorage(
    std::shared_ptr<const utils::FileAccess> fileAccessInit,
    std::shared_ptr<const DictionarySerializer> serializerInit)
    : fileAccess{std::move(fileAccessInit)}, serializer{std::move(serializerInit)}

{
    loadFile();
}

void DictionaryPersistentStorage::addDictionary(const DictionaryName& dictionaryName)
{
    storage.addDictionary(dictionaryName);
    serialize();
}

void DictionaryPersistentStorage::addDictionary(const Dictionary& dictionary)
{
    storage.addDictionary(dictionary);
    serialize();
}

void DictionaryPersistentStorage::addWordToDictionary(const DictionaryWord& dictionaryWord,
                                                      const DictionaryName& dictionaryName)
{
    storage.addWordToDictionary(dictionaryWord, dictionaryName);
    serialize();
}

void DictionaryPersistentStorage::removeDictionary(const DictionaryName& dictionaryName)
{
    storage.removeDictionary(dictionaryName);
    serialize();
}

void DictionaryPersistentStorage::removeWordFromDictionary(const std::string& englishWord,
                                                           const DictionaryName& dictionaryName)
{
    storage.removeWordFromDictionary(englishWord, dictionaryName);
    serialize();
}

boost::optional<Dictionary>
DictionaryPersistentStorage::getDictionary(const DictionaryName& dictionaryName) const
{
    return storage.getDictionary(dictionaryName);
}

Dictionaries DictionaryPersistentStorage::getDictionaries() const
{
    return storage.getDictionaries();
}

bool DictionaryPersistentStorage::containsDictionary(const DictionaryName& dictionaryName) const
{
    return storage.containsDictionary(dictionaryName);
}

Dictionaries::size_type DictionaryPersistentStorage::size() const
{
    return storage.size();
}

bool DictionaryPersistentStorage::empty() const
{
    return storage.empty();
}

void DictionaryPersistentStorage::loadFile()
{
    if (fileAccess->exists(filename))
    {
        const auto dictionaries = serializer->deserialize(fileAccess->readContent(filename));
        for (const auto& dictionary : dictionaries)
        {
            storage.addDictionary(dictionary);
        }
    }
    else
    {
        std::cerr << "Error while serializing dictionaries";
    }
}

void DictionaryPersistentStorage::serialize() const
{
    if (fileAccess->exists(filename))
    {
        fileAccess->write(filename, serializer->serialize(storage.getDictionaries()));
    }
    else
    {
        std::cerr << "Error while serializing dictionaries";
    }
}

}