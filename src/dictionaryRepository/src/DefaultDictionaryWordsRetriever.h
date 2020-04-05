#pragma once

#include <memory>

#include "DictionaryFinder.h"
#include "DictionaryWordSelector.h"
#include "repository/DictionaryRepository.h"
#include "DictionaryWordsRetriever.h"

namespace glossary::dictionaryService
{
class DefaultDictionaryWordsRetriever : public DictionaryWordsRetriever
{
public:
    explicit DefaultDictionaryWordsRetriever(std::shared_ptr<DictionaryRepository>);

    DictionaryWords retrieveDictionaryWords(const DictionaryName&) const override;

private:
    std::shared_ptr<DictionaryRepository> dictionaryRepository;
    DictionaryFinder dictionaryFinder;
    DictionaryWordSelector dictionaryWordSelector;
};
}