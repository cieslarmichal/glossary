#pragma once

#include <memory>

#include "DictionaryNameSelector.h"
#include "DictionaryNamesRetriever.h"
#include "repository/DictionaryRepository.h"

namespace glossary::dictionaryService
{
class DefaultDictionaryNamesRetriever : public DictionaryNamesRetriever
{
public:
    explicit DefaultDictionaryNamesRetriever(std::shared_ptr<DictionaryRepository>);

    DictionaryNames retrieveDictionaryNames() const override;

private:
    std::shared_ptr<DictionaryRepository> dictionaryRepository;
    DictionaryNameSelector dictionaryNameSelector;
};
}