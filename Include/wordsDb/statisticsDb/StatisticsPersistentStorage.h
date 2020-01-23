#pragma once

#include <memory>

#include "FileAccess.h"
#include "StatisticsStorage.h"
#include "wordsDb/statisticsDb/StatisticsMemoryStorage.h"
#include "wordsDb/statisticsDb/StatisticsSerializer.h"

namespace wordsDb::statisticsDb
{
class StatisticsPersistentStorage : public StatisticsStorage
{

public:
    StatisticsPersistentStorage(std::shared_ptr<const FileAccess>,
                                std::shared_ptr<const StatisticsSerializer>);

    boost::optional<WordStatistics>
    getWordStatistics(const EnglishWord&) const override;
    Statistics getStatistics() const override;
    void addWordStatistics(WordStatistics) override;
    void addCorrectAnswer(const EnglishWord&) override;
    void addIncorrectAnswer(const EnglishWord&) override;
    void resetStatistics() override;
    bool contains(const EnglishWord&) const override;
    Statistics::size_type size() const override;
    bool empty() const override;
    Statistics::const_iterator begin() const override;
    Statistics::const_iterator end() const override;

private:
    void loadFile();
    void serialize() const;

    std::shared_ptr<const FileAccess> fileAccess;
    std::shared_ptr<const StatisticsSerializer> serializer;
    StatisticsMemoryStorage storage;

    static const std::string directory;
    static const std::string filename;
};
}