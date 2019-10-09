#pragma once
#include "DictionaryAvailabilityHandler.h"
#include "FileAccess.h"

class DictionaryAvailabilityHandlerImpl : public DictionaryAvailabilityHandler
{
public:
    explicit DictionaryAvailabilityHandlerImpl(FileAccess &);

    DictionaryAvailability read() const override;
    void add(const WordAvailability&) const override;

private:
    DictionaryAvailability processDictionaryAvailabilityContent(const std::string&) const;
    WordAvailability getWordAvailability(const std::string&) const;

    FileAccess & fileAccess;
};
