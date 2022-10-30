#pragma once

#include "gmock/gmock.h"

#include "AddIncorrectAnswerCommand.h"

namespace glossary::statistics
{
class AddIncorrectAnswerCommandMock : public AddIncorrectAnswerCommand
{
public:
    MOCK_METHOD(void, addIncorrectAnswer, (const std::string& englishWord), ());
};
}
