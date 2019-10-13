#pragma once

#include "AnswerCounter.h"
#include "FileAccess.h"
#include <memory>

class PersistentAnswerCounter : public AnswerCounter
{
public:
    PersistentAnswerCounter(std::shared_ptr<const FileAccess>);
    //std::shared_ptr<const AnswersStatisticsSerializer>);

    void addCorrectAnswer() const override;
    void addIncorrectAnswer() const override;

private:
    void loadFile();
    void serialize() const;

    std::shared_ptr<const FileAccess> fileAccess;
    //std::shared_ptr<const AnswerSerialzer> serializer;
    //AnswerStatistics statistics; type: EnglishWord englishName, int correctAnswers, int incorrectAnswers

    static const std::string fileDirectory;
    static const std::string fileName;
    static const std::string filePath;
};