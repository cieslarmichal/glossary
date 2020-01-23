#include "wordsDb/descriptionsDb/DescriptionsPersistentStorage.h"

#include <iostream>

#include "exceptions/FileNotFound.h"

namespace wordsDb::descriptionsDb
{
const std::string DescriptionsPersistentStorage::directory{"../database"};
const std::string DescriptionsPersistentStorage::filename{directory +
                                                          "/words.txt"};

DescriptionsPersistentStorage::DescriptionsPersistentStorage(
    std::shared_ptr<const FileAccess> fileAccessInit,
    std::shared_ptr<const DescriptionsSerializer> serializerInit)
    : fileAccess{std::move(fileAccessInit)}, serializer{
                                                 std::move(serializerInit)}
{
    loadFile();
}

void DescriptionsPersistentStorage::addWordDescription(
    const WordDescription& word)
{
    storage.addWordDescription(word);
    serialize();
}

boost::optional<WordDescription>
DescriptionsPersistentStorage::getWordDescription(
    const EnglishWord& englishName) const
{
    return storage.getWordDescription(englishName);
}

WordsDescriptions DescriptionsPersistentStorage::getWordsDescriptions() const
{
    return storage.getWordsDescriptions();
}

bool DescriptionsPersistentStorage::contains(
    const EnglishWord& englishWord) const
{
    return storage.contains(englishWord);
}

WordsDescriptions::size_type DescriptionsPersistentStorage::size() const
{
    return storage.size();
}

bool DescriptionsPersistentStorage::empty() const
{
    return storage.empty();
}

WordsDescriptions::const_iterator DescriptionsPersistentStorage::begin() const
{
    return storage.begin();
}

WordsDescriptions::const_iterator DescriptionsPersistentStorage::end() const
{
    return storage.end();
}

void DescriptionsPersistentStorage::serialize() const
{
    try
    {
        fileAccess->write(
            filename, serializer->serialize(storage.getWordsDescriptions()));
    }
    catch (const exceptions::FileNotFound& e)
    {
        std::cerr << e.what();
    }
}

void DescriptionsPersistentStorage::loadFile()
{
    WordsDescriptions words;
    try
    {
        words = serializer->deserialize(fileAccess->readContent(filename));
    }
    catch (const exceptions::FileNotFound& e)
    {
        std::cerr << e.what();
        return;
    }

    for (const auto& word : words)
    {
        storage.addWordDescription(word);
    }
}
}