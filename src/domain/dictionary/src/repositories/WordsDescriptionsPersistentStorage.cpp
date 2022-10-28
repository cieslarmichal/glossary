#include "WordsDescriptionsPersistentStorage.h"

#include <iostream>

#include "fileSystem/GetProjectPath.h"
#include "fileSystem/exceptions/FileNotFound.h"

namespace glossary::dictionary
{
const std::string WordsDescriptionsPersistentStorage::directory{
    common::fileSystem::getProjectPath("glossary") + "repositoryFiles/"};
const std::string WordsDescriptionsPersistentStorage::filename{directory + "wordsDescriptions.txt"};

WordsDescriptionsPersistentStorage::WordsDescriptionsPersistentStorage(
    std::shared_ptr<const common::fileSystem::FileAccess> fileAccessInit,
    std::shared_ptr<const WordsDescriptionsSerializer> serializerInit)
    : fileAccess{std::move(fileAccessInit)}, serializer{std::move(serializerInit)}
{
    loadFile();
}

void WordsDescriptionsPersistentStorage::addWordDescription(const WordDescription& word)
{
    storage.addWordDescription(word);
    serialize();
}

std::optional<WordDescription>
WordsDescriptionsPersistentStorage::getWordDescription(const std::string& englishName) const
{
    return storage.getWordDescription(englishName);
}

WordsDescriptions WordsDescriptionsPersistentStorage::getWordsDescriptions() const
{
    return storage.getWordsDescriptions();
}

bool WordsDescriptionsPersistentStorage::contains(const std::string& englishWord) const
{
    return storage.contains(englishWord);
}

WordsDescriptions::size_type WordsDescriptionsPersistentStorage::size() const
{
    return storage.size();
}

bool WordsDescriptionsPersistentStorage::empty() const
{
    return storage.empty();
}

void WordsDescriptionsPersistentStorage::loadFile()
{
    WordsDescriptions words;
    try
    {
        words = serializer->deserialize(fileAccess->readContent(filename));
    }
    catch (const common::fileSystem::exceptions::FileNotFound& e)
    {
        std::cerr << "Error while serializing words descriptions " << e.what();
        return;
    }

    for (const auto& word : words)
    {
        storage.addWordDescription(word);
    }
}

void WordsDescriptionsPersistentStorage::serialize() const
{
    try
    {
        fileAccess->write(filename, serializer->serialize(storage.getWordsDescriptions()));
    }
    catch (const common::fileSystem::exceptions::FileNotFound& e)
    {
        std::cerr << "Error while serializing words descriptions " << e.what();
    }
}
}