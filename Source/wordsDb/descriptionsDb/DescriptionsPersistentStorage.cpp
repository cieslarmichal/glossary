#include <iostream>

#include "exceptions/FileNotFound.h"
#include "wordsDb/descriptionsDb/DescriptionsPersistentStorage.h"

namespace wordsDb::descriptionsDb
{
const std::string DescriptionsPersistentStorage::fileDirectory{"../database"};
const std::string DescriptionsPersistentStorage::fileName{"/words.txt"};
const std::string DescriptionsPersistentStorage::filePath{fileDirectory + fileName};

DescriptionsPersistentStorage::DescriptionsPersistentStorage(
    std::shared_ptr<const FileAccess> fileAccessInit,
    std::shared_ptr<const DescriptionsSerializer> serializerInit)
    : fileAccess{std::move(fileAccessInit)}, serializer{
                                                 std::move(serializerInit)}
{
    loadFile();
}

void DescriptionsPersistentStorage::addWord(const WordDescription& word)
{
    storage.addWord(word);
    serialize();
}

boost::optional<WordDescription>
DescriptionsPersistentStorage::getWord(const EnglishWord& englishName) const
{
    return storage.getWord(englishName);
}

Words DescriptionsPersistentStorage::getWords() const
{
    return storage.getWords();
}

bool DescriptionsPersistentStorage::contains(
    const EnglishWord& englishWord) const
{
    return storage.contains(englishWord);
}

Words::size_type DescriptionsPersistentStorage::size() const
{
    return storage.size();
}

bool DescriptionsPersistentStorage::empty() const
{
    return storage.empty();
}

Words::const_iterator DescriptionsPersistentStorage::begin() const
{
    return storage.begin();
}

Words::const_iterator DescriptionsPersistentStorage::end() const
{
    return storage.end();
}

void DescriptionsPersistentStorage::serialize() const
{
    try
    {
        fileAccess->write(filePath, serializer->serialize(storage.getWords()));
    }
    catch (const exceptions::FileNotFound& e)
    {
        std::cerr << e.what();
    }
}

void DescriptionsPersistentStorage::loadFile()
{
    Words words;
    try
    {
        words = serializer->deserialize(fileAccess->readContent(filePath));
    }
    catch (const exceptions::FileNotFound& e)
    {
        std::cerr << e.what();
        return;
    }

    for (const auto& word : words)
    {
        storage.addWord(word);
    }
}
}