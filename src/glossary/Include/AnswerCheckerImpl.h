#pragma once

#include "AnswerChecker.h"
#include "PolishWord.h"

class AnswerCheckerImpl : public AnswerChecker
{
public:
    bool correctWordAnswer(const UserInput&, const PolishWord&) const override;
    bool yesAnswer(const UserInput&) const override;
};
