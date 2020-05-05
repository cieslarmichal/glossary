#include "DictionaryObserverService.h"

#include <algorithm>

namespace glossary::dictionaryService
{

void DictionaryObserverService::registerObserver(DictionaryObserver* observer)
{
    observers.push_back(observer);
}

void DictionaryObserverService::removeObserver(DictionaryObserver* observer)
{
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void DictionaryObserverService::notifyObservers(const EnglishWords& englishWords)
{
    for (const auto& observer : observers)
    {
        if (observer)
        {
            observer->update(englishWords);
        }
    }
}
}