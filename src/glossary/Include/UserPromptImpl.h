#pragma once

#include "UserPrompt.h"

class UserPromptImpl : public UserPrompt
{
public:
    UserInput getInput() const override;
    UserInput yesPrompt() const override;

private:
    std::string getValidString() const;
    bool yesNoAnswerIsInvalid(const std::string&) const;
    void clearInputBuffer() const;
};