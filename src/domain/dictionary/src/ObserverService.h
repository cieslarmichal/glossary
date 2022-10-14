#pragma once

#include "DictionaryObserver.h"

namespace glossary::dictionary
{
class ObserverService
{
public:
    virtual ~ObserverService() = default;

    virtual void registerObserver(DictionaryObserver*) = 0;
    virtual void removeObserver(DictionaryObserver*) = 0;
    virtual void notifyObservers(const std::vector<std::string>&) = 0;
};
}
