#pragma once

#include "gmock/gmock.h"

#include "DictionarySynchronizer.h"

namespace glossary
{
class DictionarySynchronizerMock : public DictionarySynchronizer
{
public:
    MOCK_METHOD1(synchronizeDictionary, void(const dictionaryService::DictionaryName&));
    MOCK_METHOD0(synchronizeDictionaries, void());
};
}
