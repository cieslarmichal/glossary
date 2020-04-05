#pragma once

#include <memory>

#include "DictionaryFinder.h"
#include "DictionaryWordSelector.h"
#include "DictionaryWordsRetriever.h"
#include "repository/DictionaryRepository.h"

namespace glossary::dictionaryService
{
class DefaultDictionaryWordsRetriever : public DictionaryWordsRetriever
{
public:
    explicit DefaultDictionaryWordsRetriever(std::shared_ptr<repository::DictionaryRepository>);

    DictionaryWords retrieveDictionaryWords(const DictionaryName&) const override;

private:
    std::shared_ptr<repository::DictionaryRepository> dictionaryRepository;
    DictionaryFinder dictionaryFinder;
    DictionaryWordSelector dictionaryWordSelector;
};
}