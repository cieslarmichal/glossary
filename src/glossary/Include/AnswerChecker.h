#pragma once

#include "PolishWord.h"
#include "UserInput.h"

class AnswerChecker
{
public:
    virtual ~AnswerChecker() = default;

    virtual bool correctWordAnswer(const UserInput&, const PolishWord&) const = 0;
    virtual bool yesAnswer(const UserInput&) const = 0;
};
