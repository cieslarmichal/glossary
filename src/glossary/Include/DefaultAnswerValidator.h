#pragma once

#include "AnswerValidator.h"

namespace glossary
{
class DefaultAnswerValidator : public AnswerValidator
{
public:
    bool validateAnswer(const std::string& answer, const std::string& expectedAnswer) const override;
    bool validateYesAnswer(const std::string& answer) const override;
};
}