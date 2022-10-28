#pragma once

#include "gmock/gmock.h"

#include "CreateDictionaryCommand.h"

namespace glossary::dictionary
{
class CreateDictionaryCommandMock : public CreateDictionaryCommand
{
public:
    MOCK_METHOD(void, createDictionary, (const std::string& dictionaryName), ());
};
}
