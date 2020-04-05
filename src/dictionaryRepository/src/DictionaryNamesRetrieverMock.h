#pragma once

#include "gmock/gmock.h"
#include "DictionaryNamesRetriever.h"

namespace glossary::dictionaryService
{
class DictionaryNamesRetrieverMock : public DictionaryNamesRetriever
{
public:
    MOCK_CONST_METHOD0(retrieveDictionaryNames, DictionaryNames());
};
}