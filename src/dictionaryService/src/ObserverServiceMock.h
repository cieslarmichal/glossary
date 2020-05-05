#pragma once

#include "gmock/gmock.h"

#include "ObserverService.h"

namespace glossary::dictionaryService
{
class ObserverServiceMock : public ObserverService
{
public:
    MOCK_METHOD1(registerObserver, void(DictionaryObserver*));
    MOCK_METHOD1(removeObserver, void(DictionaryObserver*));
    MOCK_METHOD1(notifyObservers, void(const EnglishWords&));
};
}