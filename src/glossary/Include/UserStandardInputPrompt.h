#pragma once

#include "UserPrompt.h"

class UserStandardInputPrompt : public UserPrompt
{
public:
    UserInput getStringInput() const override;
    int getIntInput() const override;
    UserInput yesPrompt() const override;

private:
    std::string getValidString() const;
    int getValidInt() const;
    bool yesNoAnswerIsInvalid(const std::string&) const;
    void clearInputBuffer() const;
};