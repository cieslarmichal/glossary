#pragma once

#include "DictionaryObserver.h"


namespace glossary::dictionaryService
{
class ObserverService
{
public:
    virtual ~ObserverService() = default;

    virtual void registerObserver(DictionaryObserver*) = 0;
    virtual void removeObserver(DictionaryObserver*) = 0;
    virtual void notifyObservers(const EnglishWords&) = 0;
};
}
