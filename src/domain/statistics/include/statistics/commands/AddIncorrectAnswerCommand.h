#pragma once

#include <string>

namespace glossary::statistics
{
class AddIncorrectAnswerCommand
{
public:
    virtual ~AddIncorrectAnswerCommand() = default;

    virtual void addIncorrectAnswer(const std::string& englishWord) = 0;
};
}
