#pragma once

#include "gmock/gmock.h"

#include "AddCorrectAnswerCommand.h"

namespace glossary::statistics
{
class AddCorrectAnswerCommandMock : public AddCorrectAnswerCommand
{
public:
    MOCK_METHOD(void, addCorrectAnswer, (const std::string& englishWord), ());
};
}
