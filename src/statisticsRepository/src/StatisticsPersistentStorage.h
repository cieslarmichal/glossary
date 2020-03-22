#pragma once

#include <memory>

#include "StatisticsMemoryStorage.h"
#include "StatisticsSerializer.h"
#include "StatisticsStorage.h"
#include "utils/FileAccess.h"

namespace statisticsRepository
{
class StatisticsPersistentStorage : public StatisticsStorage
{
public:
    StatisticsPersistentStorage(std::shared_ptr<const utils::FileAccess>,
                                std::shared_ptr<const StatisticsSerializer>);

    boost::optional<WordStatistics> getWordStatistics(const EnglishWord&) const override;
    Statistics getStatistics() const override;
    void addWordStatistics(WordStatistics) override;
    void addCorrectAnswer(const EnglishWord&) override;
    void addIncorrectAnswer(const EnglishWord&) override;
    void resetStatistics() override;
    bool contains(const EnglishWord&) const override;
    Statistics::size_type size() const override;
    bool empty() const override;

private:
    void loadFile();
    void serialize() const;

    std::shared_ptr<const utils::FileAccess> fileAccess;
    std::shared_ptr<const StatisticsSerializer> serializer;
    StatisticsMemoryStorage storage;

    static const std::string directory;
    static const std::string filename;
};
}