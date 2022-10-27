#pragma once

#include <memory>

#include "DictionaryFinder.h"
#include "DictionaryWordAccumulator.h"
#include "DictionaryWordRandomizer.h"
#include "RandomDictionaryWordRetriever.h"
#include "repository/DictionaryRepository.h"

namespace glossary::dictionary
{
class DefaultRandomDictionaryWordRetriever : public RandomDictionaryWordRetriever
{
public:
    DefaultRandomDictionaryWordRetriever(std::shared_ptr<DictionaryRepository>,
                                         std::unique_ptr<DictionaryWordRandomizer>);

    std::optional<DictionaryWord> getRandomDictionaryWord() const override;
    std::optional<DictionaryWord> getRandomDictionaryWord(const std::string&) const override;

private:
    std::optional<DictionaryWord> randomizeDictionaryWord(const std::vector<DictionaryWord>&) const;

    std::shared_ptr<DictionaryRepository> dictionaryRepository;
    std::unique_ptr<DictionaryWordRandomizer> dictionaryWordRandomizer;
    DictionaryWordAccumulator dictionaryWordAccumulator;
    DictionaryFinder dictionaryFinder;
};
}
