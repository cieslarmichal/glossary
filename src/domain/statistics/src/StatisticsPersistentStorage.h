#pragma once

#include <memory>

#include "../../../common/fileSystem/include/FileAccess.h"
#include "StatisticsMemoryStorage.h"
#include "StatisticsSerializer.h"
#include "StatisticsStorage.h"

namespace glossary::statistics
{
class StatisticsPersistentStorage : public StatisticsStorage
{
public:
    StatisticsPersistentStorage(std::shared_ptr<const common::FileAccess>,
                                std::shared_ptr<const StatisticsSerializer>);

    std::optional<WordStatistics> getWordStatistics(const std::string&) const override;
    std::vector<WordStatistics> getStatistics() const override;
    void addWordStatistics(WordStatistics) override;
    void addCorrectAnswer(const std::string&) override;
    void addIncorrectAnswer(const std::string&) override;
    void resetStatistics() override;
    bool contains(const std::string&) const override;
    std::vector<WordStatistics>::size_type size() const override;
    bool empty() const override;

private:
    void loadFile();
    void serialize() const;

    std::shared_ptr<const common::FileAccess> fileAccess;
    std::shared_ptr<const StatisticsSerializer> serializer;
    StatisticsMemoryStorage storage;

    static const std::string directory;
    static const std::string filename;
};
}