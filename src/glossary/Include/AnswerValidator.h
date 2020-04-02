#pragma once

#include "PolishWord.h"
#include "UserInput.h"

namespace glossary
{
class AnswerValidator
{
public:
    virtual ~AnswerValidator() = default;

    virtual bool validateAnswer(const UserInput&, const PolishWord&) const = 0;
    virtual bool validateYesAnswer(const UserInput&) const = 0;
};
}