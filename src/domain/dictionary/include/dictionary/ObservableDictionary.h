#pragma once

#include "DictionaryObserver.h"

namespace glossary::dictionary
{
class ObservableDictionary
{
public:
    virtual ~ObservableDictionary() = default;

    virtual void registerObserver(DictionaryObserver*) = 0;
    virtual void removeObserver(DictionaryObserver*) = 0;

protected:
    virtual void notifyObservers(const std::vector<std::string>&) = 0;
};
}
