#pragma once

#include <memory>

#include "DictionaryWordRandomizer.h"
#include "utils/RandomNumberGenerator.h"

namespace glossary::dictionaryService
{
class DefaultDictionaryWordRandomizer : public DictionaryWordRandomizer
{
public:
    explicit DefaultDictionaryWordRandomizer(std::shared_ptr<utils::RandomNumberGenerator>);

    DictionaryWord randomize(const DictionaryWords&) const override;

private:
    std::shared_ptr<utils::RandomNumberGenerator> randomNumberGenerator;
    int getRandomIndex(DictionaryWords::size_type) const;
};
}