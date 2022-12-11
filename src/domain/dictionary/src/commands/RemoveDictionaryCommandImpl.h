#pragma once

#include <memory>

#include "../repositories/DictionaryRepository.h"
#include "commands/RemoveDictionaryCommand.h"

namespace glossary::dictionary
{
class RemoveDictionaryCommandImpl : public RemoveDictionaryCommand
{
public:
    explicit RemoveDictionaryCommandImpl(std::shared_ptr<DictionaryRepository>);

    void removeDictionary(const std::string& dictionaryName) override;

private:
    std::shared_ptr<DictionaryRepository> dictionaryRepository;
};
}
