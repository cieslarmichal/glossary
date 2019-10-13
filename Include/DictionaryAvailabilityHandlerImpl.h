#pragma once

#include "DictionaryAvailabilityHandler.h"
#include "FileAccess.h"
#include <memory>

class DictionaryAvailabilityHandlerImpl : public DictionaryAvailabilityHandler
{
public:
    explicit DictionaryAvailabilityHandlerImpl(std::shared_ptr<const FileAccess>);

    DictionaryAvailability read() const override;
    void add(const WordAvailability&) const override;

private:
    DictionaryAvailability processDictionaryAvailabilityContent(const std::string&) const;
    WordAvailability getWordAvailability(const std::string&) const;

    std::shared_ptr<const FileAccess> fileAccess;

    static const std::string dictionaryAvailabilityFilePath;
};
