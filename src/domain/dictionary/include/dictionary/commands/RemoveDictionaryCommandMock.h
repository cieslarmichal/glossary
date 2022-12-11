#pragma once

#include "gmock/gmock.h"

#include "RemoveDictionaryCommand.h"

namespace glossary::dictionary
{
class RemoveDictionaryCommandMock : public RemoveDictionaryCommand
{
public:
    MOCK_METHOD(void, removeDictionary, (const std::string& dictionaryName), ());
};
}
