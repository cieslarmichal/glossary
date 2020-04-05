#pragma once

#include <memory>

#include "DictionaryFinder.h"
#include "DictionaryWordSelector.h"
#include "DictionaryWordRandomizer.h"
#include "RandomDictionaryWordRetriever.h"
#include "repository/DictionaryRepository.h"

namespace glossary::dictionaryService
{
class DefaultRandomDictionaryWordRetriever : public RandomDictionaryWordRetriever
{
public:
    DefaultRandomDictionaryWordRetriever(std::shared_ptr<DictionaryRepository>,
                                         std::unique_ptr<DictionaryWordRandomizer>);

    boost::optional<DictionaryWord> getRandomDictionaryWord() const override;
    boost::optional<DictionaryWord> getRandomDictionaryWord(const DictionaryName&) const override;

private:
    boost::optional<DictionaryWord> randomizeDictionaryWord(const DictionaryWords&) const;

    std::shared_ptr<DictionaryRepository> dictionaryRepository;
    std::unique_ptr<DictionaryWordRandomizer> dictionaryWordRandomizer;
    DictionaryWordSelector dictionaryWordSelector;
    DictionaryFinder dictionaryFinder;
};
}
