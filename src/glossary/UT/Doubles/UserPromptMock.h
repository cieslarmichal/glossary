#pragma once

#include "gmock/gmock.h"

#include "UserPrompt.h"

namespace glossary
{
class UserPromptMock : public UserPrompt
{
public:
    MOCK_CONST_METHOD0(getStringInput, std::string());
    MOCK_CONST_METHOD0(getNumberInput, int());
};
}
