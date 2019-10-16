#pragma once

#include "AnswerChecker.h"

class AnswerCheckerImpl : public AnswerChecker
{
public:
    bool correctWordAnswer(const UserInput&, const EnglishWord&) const override;
    bool yesAnswer(const UserInput&) const override;
};
