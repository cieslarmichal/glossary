#pragma once

#include "ObserverService.h"

namespace glossary::dictionaryService
{
class DictionaryObserverService : public ObserverService
{
public:
    void registerObserver(DictionaryObserver* observer) override;
    void removeObserver(DictionaryObserver* observer) override;
    void notifyObservers(const EnglishWords&) override;

private:
    std::vector<DictionaryObserver*> observers;
};
}
