#pragma once

#include "ObserverService.h"

namespace glossary::dictionary
{
class DictionaryObserverService : public ObserverService
{
public:
    void registerObserver(DictionaryObserver* observer) override;
    void removeObserver(DictionaryObserver* observer) override;
    void notifyObservers(const std::vector<std::string>&) override;

private:
    std::vector<DictionaryObserver*> observers;
};
}
