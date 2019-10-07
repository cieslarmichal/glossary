#pragma once
#include "WordAvailability.h"
#include <map>
#include "FileAccess.h"

class DictionaryAvailabilityHandler
{
public:
    explicit DictionaryAvailabilityHandler(FileAccess &);

    std::map<EnglishWord, WordAvailability> read() const;
    void add(const WordAvailability&) const;

private:
    std::map<EnglishWord, WordAvailability> processDictionaryAvailabilityContent(const std::string&) const;
    WordAvailability getWordAvailability(const std::string&) const;

    FileAccess & fileAccess;
};