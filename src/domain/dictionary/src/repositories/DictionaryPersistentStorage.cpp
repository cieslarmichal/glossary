#include "DictionaryPersistentStorage.h"

#include <iostream>

#include "fileSystem/GetProjectPath.h"

namespace glossary::dictionary
{
const std::string DictionaryPersistentStorage::directory{common::fileSystem::getProjectPath("glossary") +
                                                         "repositoryFiles/"};
const std::string DictionaryPersistentStorage::filename{directory + "dictionaries.txt"};

DictionaryPersistentStorage::DictionaryPersistentStorage(
    std::shared_ptr<const common::fileSystem::FileAccess> fileAccessInit,
    std::shared_ptr<const DictionarySerializer> serializerInit)
    : fileAccess{std::move(fileAccessInit)}, serializer{std::move(serializerInit)}

{
    loadFile();
}

void DictionaryPersistentStorage::addDictionary(const std::string& dictionaryName)
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
                                                      const std::string& dictionaryName)
{
    storage.addWordToDictionary(dictionaryWord, dictionaryName);
    serialize();
}

void DictionaryPersistentStorage::removeDictionary(const std::string& dictionaryName)
{
    storage.removeDictionary(dictionaryName);
    serialize();
}

void DictionaryPersistentStorage::removeWordFromDictionary(const std::string& englishWord,
                                                           const std::string& dictionaryName)
{
    storage.removeWordFromDictionary(englishWord, dictionaryName);
    serialize();
}

void DictionaryPersistentStorage::changeWordTranslationFromDictionary(const std::string& englishWord,
                                                                      const std::string& translation,
                                                                      const std::string& dictionaryName)
{
    storage.changeWordTranslationFromDictionary(englishWord, translation, dictionaryName);
    serialize();
}

std::optional<Dictionary> DictionaryPersistentStorage::getDictionary(const std::string& dictionaryName) const
{
    return storage.getDictionary(dictionaryName);
}

std::vector<Dictionary> DictionaryPersistentStorage::getDictionaries() const
{
    return storage.getDictionaries();
}

bool DictionaryPersistentStorage::containsDictionary(const std::string& dictionaryName) const
{
    return storage.containsDictionary(dictionaryName);
}

std::vector<Dictionary>::size_type DictionaryPersistentStorage::size() const
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
            storage.addDictionary(dictionary);
    }
    else
    {
        std::cerr << "Error while serializing dictionaries";
    }
}

void DictionaryPersistentStorage::serialize() const
{
    if (fileAccess->exists(filename))
        fileAccess->write(filename, serializer->serialize(storage.getDictionaries()));
    else
        std::cerr << "Error while serializing dictionaries";
}

}
