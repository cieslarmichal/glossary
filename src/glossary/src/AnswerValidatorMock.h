#pragma once

#include "gmock/gmock.h"

#include "AnswerValidator.h"

namespace glossary
{
class AnswerValidatorMock : public AnswerValidator
{
public:
    MOCK_CONST_METHOD2(validateAnswer, bool(const std::string& answer, const std::string& expectedAnswer));
};
}
