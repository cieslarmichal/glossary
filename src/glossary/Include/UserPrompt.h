#pragma once

#include <string>

namespace glossary
{
class UserPrompt
{
public:
    virtual ~UserPrompt() = default;

    virtual std::string getStringInput() const = 0;
    virtual int getIntInput() const = 0;
    virtual std::string yesPrompt() const = 0;
};
}