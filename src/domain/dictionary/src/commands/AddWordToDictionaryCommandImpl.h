#pragma once

#include <memory>

#include "../repositories/DictionaryRepository.h"
#include "commands/AddWordToDictionaryCommand.h"

namespace glossary::dictionary
{
class AddWordToDictionaryCommandImpl : public AddWordToDictionaryCommand
{
public:
    explicit AddWordToDictionaryCommandImpl(std::shared_ptr<DictionaryRepository>);

    void addWordToDictionary(const std::string& dictionaryName, const DictionaryWord&) override;

private:
    std::shared_ptr<DictionaryRepository> dictionaryRepository;
};
}
