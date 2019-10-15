#pragma once

#include "AnswerChecker.h"


class AnswerCheckerImpl : public AnswerChecker
{
public:
    bool checkAnswer(const UserInput&, const EnglishWord&) const override;

private:
    bool areEqual(const UserInput&, const EnglishWord&) const;
};
