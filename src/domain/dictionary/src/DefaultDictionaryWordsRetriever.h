#pragma once

#include <memory>

#include "DictionaryFinder.h"
#include "DictionaryWordAccumulator.h"
#include "DictionaryWordsRetriever.h"
#include "repository/DictionaryRepository.h"

namespace glossary::dictionary
{
class DefaultDictionaryWordsRetriever : public DictionaryWordsRetriever
{
public:
    explicit DefaultDictionaryWordsRetriever(std::shared_ptr<repository::DictionaryRepository>);

    std::optional<std::vector<DictionaryWord>>
    retrieveDictionaryWords(const std::string&) const override;
    std::optional<std::vector<std::string>> retrieveEnglishWords(const std::string&) const override;
    std::vector<std::string> retrieveEnglishWords() const override;

private:
    std::optional<Dictionary> getDictionary(const std::string&) const;

    std::shared_ptr<repository::DictionaryRepository> dictionaryRepository;
    DictionaryFinder dictionaryFinder;
    DictionaryWordAccumulator dictionaryWordAccumulator;
};
}