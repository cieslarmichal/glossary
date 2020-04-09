#pragma once

#include <string>

namespace glossary
{
class UserPrompt
{
public:
    virtual ~UserPrompt() = default;

    virtual std::string getStringInput() const = 0;
    virtual int getNumberInput() const = 0;
};
}