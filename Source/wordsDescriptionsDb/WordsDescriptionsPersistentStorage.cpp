#include "wordsDescriptionsDb/WordsDescriptionsPersistentStorage.h"

#include <iostream>

#include "exceptions/FileNotFound.h"

namespace wordsDescriptionsDb
{
const std::string WordsDescriptionsPersistentStorage::directory{"../database"};
const std::string WordsDescriptionsPersistentStorage::filename{
    directory + "/wordsDescriptions.txt"};

WordsDescriptionsPersistentStorage::WordsDescriptionsPersistentStorage(
    std::shared_ptr<const utils::FileAccess> fileAccessInit,
    std::shared_ptr<const WordsDescriptionsSerializer> serializerInit)
    : fileAccess{std::move(fileAccessInit)}, serializer{
                                                 std::move(serializerInit)}
{
    loadFile();
}

void WordsDescriptionsPersistentStorage::addWordDescription(
    const WordDescription& word)
{
    storage.addWordDescription(word);
    serialize();
}

boost::optional<WordDescription>
WordsDescriptionsPersistentStorage::getWordDescription(
    const EnglishWord& englishName) const
{
    return storage.getWordDescription(englishName);
}

WordsDescriptions
WordsDescriptionsPersistentStorage::getWordsDescriptions() const
{
    return storage.getWordsDescriptions();
}

bool WordsDescriptionsPersistentStorage::contains(
    const EnglishWord& englishWord) const
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

WordsDescriptions::const_iterator
WordsDescriptionsPersistentStorage::begin() const
{
    return storage.begin();
}

WordsDescriptions::const_iterator
WordsDescriptionsPersistentStorage::end() const
{
    return storage.end();
}

void WordsDescriptionsPersistentStorage::serialize() const
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

void WordsDescriptionsPersistentStorage::loadFile()
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