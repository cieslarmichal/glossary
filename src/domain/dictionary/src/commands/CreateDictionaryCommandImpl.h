#pragma once

#include <memory>

#include "../repositories/DictionaryRepository.h"
#include "commands/CreateDictionaryCommand.h"

namespace glossary::dictionary
{
class CreateDictionaryCommandImpl : public CreateDictionaryCommand
{
public:
    explicit CreateDictionaryCommandImpl(std::shared_ptr<DictionaryRepository>);

    void createDictionary(const std::string& dictionaryName) override;

private:
    std::shared_ptr<DictionaryRepository> dictionaryRepository;
};
}
