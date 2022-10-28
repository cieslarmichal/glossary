#pragma once

#include <memory>

#include "../repositories/DictionaryRepository.h"
#include "commands/UpdateWordTranslationInDictionaryCommand.h"

namespace glossary::dictionary
{
class UpdateWordTranslationInDictionaryCommandImpl : public UpdateWordTranslationInDictionaryCommand
{
public:
    explicit UpdateWordTranslationInDictionaryCommandImpl(std::shared_ptr<DictionaryRepository>);

    void updateWordTranslation(const std::string& dictionaryName, const std::string& englishWord,
                               const std::string& translation) override;

private:
    std::shared_ptr<DictionaryRepository> dictionaryRepository;
};
}
