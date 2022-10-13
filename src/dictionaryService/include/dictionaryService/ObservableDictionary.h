#pragma once

#include "DictionaryObserver.h"


namespace glossary::dictionaryService
{
class ObservableDictionary
{
public:
    virtual ~ObservableDictionary() = default;

    virtual void registerObserver(DictionaryObserver*) = 0;
    virtual void removeObserver(DictionaryObserver*) = 0;

protected:
    virtual void notifyObservers(const EnglishWords&) = 0;
};
}
