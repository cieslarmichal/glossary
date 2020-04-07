#pragma once

#include <memory>

#include "DictionaryFinder.h"
#include "DictionaryWordAccumulator.h"
#include "DictionaryWordsRetriever.h"
#include "repository/DictionaryRepository.h"

namespace glossary::dictionaryService
{
class DefaultDictionaryWordsRetriever : public DictionaryWordsRetriever
{
public:
    explicit DefaultDictionaryWordsRetriever(std::shared_ptr<repository::DictionaryRepository>);

    boost::optional<DictionaryWords> retrieveDictionaryWords(const DictionaryName&) const override;
    boost::optional<EnglishWords> retrieveEnglishWords(const DictionaryName&) const override;
    EnglishWords retrieveEnglishWords() const override;

private:
    boost::optional<Dictionary> getDictionary(const DictionaryName&) const;

    std::shared_ptr<repository::DictionaryRepository> dictionaryRepository;
    DictionaryFinder dictionaryFinder;
    DictionaryWordAccumulator dictionaryWordAccumulator;
};
}