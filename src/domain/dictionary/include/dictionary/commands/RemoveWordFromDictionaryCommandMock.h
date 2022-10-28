#pragma once

#include "gmock/gmock.h"

#include "RemoveWordFromDictionaryCommand.h"

namespace glossary::dictionary
{
class RemoveWordFromDictionaryCommandMock : public RemoveWordFromDictionaryCommand
{
public:
    MOCK_METHOD(void, removeWordFromDictionary, (const std::string& dictionaryName, const std::string& englishWord),
                ());
};
}
