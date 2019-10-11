#include <iostream>
#include "PersistentStorage.h"

const std::string PersistentStorage::fileDirectory{"../database"};
const std::string PersistentStorage::fileName{"/words.txt"};

PersistentStorage::PersistentStorage(std::shared_ptr<const FileAccess> fileAccessInit,
                                     std::shared_ptr<const WordsSerializer> serializerInit)
        : fileAccess{std::move(fileAccessInit)}, serializer{std::move(serializerInit)}
{
    loadFile();
}

void PersistentStorage::addWord(const Word& word)
{
    storage.addWord(word);
}

boost::optional<Word> PersistentStorage::getWord(const EnglishWord& englishName) const
{
    return storage.getWord(englishName);
}

Words PersistentStorage::getWords() const
{
    return storage.getWords();
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

void PersistentStorage::serialize()
{
    serializer->serialize(storage.getWords());
}

void PersistentStorage::loadFile()
{
    const auto filePath = fileDirectory + fileName;
    for(const auto & word : serializer->deserialize(fileAccess->readContent(filePath)))
    {
        storage.addWord(word);
    }
}
