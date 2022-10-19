#pragma once

#include "gmock/gmock.h"

#include "DictionaryObserver.h"

namespace glossary::dictionary
{
class DictionaryObserverMock : public DictionaryObserver
{
public:
    MOCK_METHOD1(update, void(const std::vector<std::string>&));
};
}