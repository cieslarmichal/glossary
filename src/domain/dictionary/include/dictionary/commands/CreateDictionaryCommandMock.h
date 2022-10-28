#pragma once

#include "gmock/gmock.h"

#include "CreateDictionaryCommand.h"

namespace glossary::dictionary
{
class AddDictionaryCommandMock : public AddDictionaryCommand
{
public:
    MOCK_METHOD(void, addDictionary, (const std::string& dictionaryName), ());
};
}
