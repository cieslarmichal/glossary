#pragma once

#include "AnswersCounter.h"
#include "FileAccess.h"
#include "AnswersStatisticsSerializer.h"
#include <memory>

//TODO: add statistics to internal storage as PersistentStorage (maybe template somehow)

class PersistentAnswersCounter : public AnswersCounter
{
public:
    PersistentAnswersCounter(std::shared_ptr<const FileAccess>, std::shared_ptr<const AnswersStatisticsSerializer>);

    void addCorrectAnswer(const EnglishWord&) override;
    void addIncorrectAnswer(const EnglishWord&) override;
    boost::optional<AnswersStatisticsPerWord> getAnswersStatisticsPerWord(const EnglishWord&) const override;
    AnswersStatistics getAnswersStatistics() const override;

private:
    void loadFile();
    void serialize() const;
    bool containsWord(const EnglishWord&) const;
    void addEmptyStatisticsPerWord(const EnglishWord&);

    std::shared_ptr<const FileAccess> fileAccess;
    std::shared_ptr<const AnswersStatisticsSerializer> serializer;
    AnswersStatistics statistics;

    static const std::string fileDirectory;
    static const std::string fileName;
    static const std::string filePath;
};