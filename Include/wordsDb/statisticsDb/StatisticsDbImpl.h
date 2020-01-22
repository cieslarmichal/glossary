#pragma once

#include <memory>

#include "FileAccess.h"
#include "StatisticsDb.h"
#include "StatisticsSerializer.h"

namespace wordsDb::statisticsDb
{
class StatisticsDbImpl : public StatisticsDb
{
public:
    StatisticsDbImpl(std::shared_ptr<const FileAccess>,
                     std::shared_ptr<const StatisticsSerializer>);

    void addCorrectAnswer(const EnglishWord&) override;
    void addIncorrectAnswer(const EnglishWord&) override;
    boost::optional<AnswersStatisticsPerWord>
    getAnswersStatisticsPerWord(const EnglishWord&) const override;
    AnswersStatistics getAnswersStatistics() const override;

private:
    void loadFile();
    void serialize() const;
    bool containsWord(const EnglishWord&) const;
    void addEmptyStatisticsPerWord(const EnglishWord&);

    std::shared_ptr<const FileAccess> fileAccess;
    std::shared_ptr<const StatisticsSerializer> serializer;
    AnswersStatistics statistics;

// TODO: reduce filenames to dirc and full name(dirc+name)
    static const std::string filePath;
    static const std::string fileDirectory;
    static const std::string fileName;
};
}