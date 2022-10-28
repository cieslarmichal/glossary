#pragma once

#include <memory>

#include "../repositories/DictionaryRepository.h"
#include "commands/RemoveWordFromDictionaryCommand.h"

namespace glossary::dictionary
{
class RemoveWordFromDictionaryCommandImpl : public RemoveWordFromDictionaryCommand
{
public:
    explicit RemoveWordFromDictionaryCommandImpl(std::shared_ptr<DictionaryRepository>);

    void removeWordFromDictionary(const std::string& dictionaryName, const std::string& englishWord) override;

private:
    std::shared_ptr<DictionaryRepository> dictionaryRepository;
};
}
