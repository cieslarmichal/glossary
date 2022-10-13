#include "StatisticsPersistentStorage.h"

#include <iostream>

#include "utils/GetProjectPath.h"
#include "utils/exceptions/FileNotFound.h"

namespace glossary::statistics
{

const std::string StatisticsPersistentStorage::directory{utils::getProjectPath("glossary") +
                                                         "repositoryFiles/"};
const std::string StatisticsPersistentStorage::filename{directory + "statistics.txt"};

StatisticsPersistentStorage::StatisticsPersistentStorage(
    std::shared_ptr<const utils::FileAccess> fileAccessInit,
    std::shared_ptr<const StatisticsSerializer> serializerInit)
    : fileAccess{std::move(fileAccessInit)}, serializer{std::move(serializerInit)}
{
    loadFile();
}

std::optional<WordStatistics>
StatisticsPersistentStorage::getWordStatistics(const std::string& englishWord) const
{
    return storage.getWordStatistics(englishWord);
}

std::vector<WordStatistics> StatisticsPersistentStorage::getStatistics() const
{
    return storage.getStatistics();
}

void StatisticsPersistentStorage::addWordStatistics(WordStatistics wordStatistics)
{
    if (not storage.contains(wordStatistics.getEnglishWord()))
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
    catch (const utils::exceptions::FileNotFound& e)
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
    catch (const utils::exceptions::FileNotFound& e)
    {
        std::cerr << "Error while serializing statistics " << e.what();
    }
}

}
