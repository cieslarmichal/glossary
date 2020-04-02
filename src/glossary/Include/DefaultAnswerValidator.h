#pragma once

#include "AnswerValidator.h"
#include "PolishWord.h"

namespace glossary
{
class DefaultAnswerValidator : public AnswerValidator
{
public:
    bool validateAnswer(const UserInput&, const PolishWord&) const override;
    bool validateYesAnswer(const UserInput&) const override;
};
}