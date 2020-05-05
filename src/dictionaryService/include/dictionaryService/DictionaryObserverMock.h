#pragma once

#include "gmock/gmock.h"

#include "DictionaryObserver.h"

namespace glossary::dictionaryService
{
class DictionaryObserverMock : public DictionaryObserver
{
public:
    MOCK_METHOD1(update, void(const EnglishWords&));
};
}