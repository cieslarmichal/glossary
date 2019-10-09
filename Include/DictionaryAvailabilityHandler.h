#pragma once
#include "DictionaryAvailability.h"

class DictionaryAvailabilityHandler
{
public:
    virtual ~DictionaryAvailabilityHandler() = default;

    virtual DictionaryAvailability read() const = 0;
    virtual void add(const WordAvailability&) const = 0;
};
