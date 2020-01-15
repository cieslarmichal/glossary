#include "wordsDb/PersistentStorage.h"

#include <iostream>

#include "exceptions/FileNotFound.h"

const std::string PersistentStorage::fileDirectory{"../database"};
const std::string PersistentStorage::fileName{"/words.txt"};
const std::string PersistentStorage::filePath{fileDirectory + fileName};

PersistentStorage::PersistentStorage(
    std::shared_ptr<const FileAccess> fileAccessInit,
    std::shared_ptr<const WordsSerializer> serializerInit)
    : fileAccess{std::move(fileAccessInit)}, serializer{
                                                 std::move(serializerInit)}
{
    loadFile();
}

void PersistentStorage::addWord(const Word& word)
{
    storage.addWord(word);
    serialize();
}

boost::optional<Word>
PersistentStorage::getWord(const EnglishWord& englishName) const
{
    return storage.getWord(englishName);
}

Words PersistentStorage::getWords() const
{
    return storage.getWords();
}

bool PersistentStorage::contains(const EnglishWord& englishWord) const
{
    return storage.contains(englishWord);
}

Words::size_type PersistentStorage::size() const
{
    return storage.size();
}

bool PersistentStorage::empty() const
{
    return storage.empty();
}

Words::const_iterator PersistentStorage::begin() const
{
    return storage.begin();
}

Words::const_iterator PersistentStorage::end() const
{
    return storage.end();
}

void PersistentStorage::serialize() const
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

void PersistentStorage::loadFile()
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
