#pragma once

#include "UserPrompt.h"

namespace glossary
{
class UserStandardInputPrompt : public UserPrompt
{
public:
    std::string getStringInput() const override;
    int getIntInput() const override;
    std::string yesPrompt() const override;

private:
    std::string getValidString() const;
    int getValidInt() const;
    bool yesNoAnswerIsInvalid(const std::string&) const;
    void clearInputBuffer() const;
};
}