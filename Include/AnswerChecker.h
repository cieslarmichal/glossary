#pragma once

#include "EnglishWord.h"
#include "UserInput.h"

class AnswerChecker
{
public:
    virtual ~AnswerChecker() = default;

    virtual bool checkAnswer(const UserInput&, const EnglishWord&) const = 0;
};
