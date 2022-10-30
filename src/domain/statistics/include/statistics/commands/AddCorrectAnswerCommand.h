#pragma once

#include <string>

namespace glossary::statistics
{
class AddCorrectAnswerCommand
{
public:
    virtual ~AddCorrectAnswerCommand() = default;

    virtual void addCorrectAnswer(const std::string& englishWord) = 0;
};
}
