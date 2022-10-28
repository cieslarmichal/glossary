#pragma once

#include "gmock/gmock.h"

#include "AddWordToDictionaryCommand.h"

namespace glossary::dictionary
{
class AddWordToDictionaryCommandMock : public AddWordToDictionaryCommand
{
public:
    MOCK_METHOD(void, addWordToDictionary, (const std::string& dictionaryName, const DictionaryWord&), ());
};
}
