#include "StatisticsPersistentStorage.h"

#include <iostream>

#include "fileSystem/exceptions/FileNotFound.h"
#include "fileSystem/GetProjectPath.h"

namespace glossary::statistics
{

const std::string StatisticsPersistentStorage::directory{common::fileSystem::getProjectPath("glossary") +
                                                         "repositoryFiles/"};
const std::string StatisticsPersistentStorage::filename{directory + "statistics.txt"};

StatisticsPersistentStorage::StatisticsPersistentStorage(
    std::shared_ptr<const common::fileSystem::FileAccess> fileAccessInit,
    std::shared_ptr<const WordsStatisticsSerializer> serializerInit)
    : fileAccess{std::move(fileAccessInit)}, serializer{std::move(serializerInit)}
{
    loadFile();
}

std::optional<WordStatistics> StatisticsPersistentStorage::getWordStatistics(const std::string& englishWord) const
{
    return storage.getWordStatistics(englishWord);
}

std::vector<WordStatistics> StatisticsPersistentStorage::getStatistics() const
{
    return storage.getStatistics();
}

void StatisticsPersistentStorage::addWordStatistics(WordStatistics wordStatistics)
{
    if (not storage.contains(wordStatistics.englishWord))
    {
        storage.addWordStatistics(std::move(wordStatistics));
        serialize();
    }
}

void StatisticsPersistentStorage::addCorrectAnswer(const std::string& englishWord)
{
    storage.addCorrectAnswer(englishWord);
    serialize();
}

void StatisticsPersistentStorage::addIncorrectAnswer(const std::string& englishWord)
{
    storage.addIncorrectAnswer(englishWord);
    serialize();
}

void StatisticsPersistentStorage::resetStatistics()
{
    storage.resetStatistics();
    serialize();
}

bool StatisticsPersistentStorage::contains(const std::string& englishWord) const
{
    return storage.contains(englishWord);
}

std::vector<WordStatistics>::size_type StatisticsPersistentStorage::size() const
{
    return storage.size();
}

bool StatisticsPersistentStorage::empty() const
{
    return storage.empty();
}

void StatisticsPersistentStorage::loadFile()
{
    std::vector<WordStatistics> statistics;
    try
    {
        statistics = serializer->deserialize(fileAccess->readContent(filename));
    }
    catch (const common::fileSystem::exceptions::FileNotFound& e)
    {
        std::cerr << "Error while deserializing statistics " << e.what();
        return;
    }

    for (const auto& wordStats : statistics)
    {
        storage.addWordStatistics(wordStats);
    }
}

void StatisticsPersistentStorage::serialize() const
{
    try
    {
        fileAccess->write(filename, serializer->serialize(storage.getStatistics()));
    }
    catch (const common::fileSystem::exceptions::FileNotFound& e)
    {
        std::cerr << "Error while serializing statistics " << e.what();
    }
}

}
