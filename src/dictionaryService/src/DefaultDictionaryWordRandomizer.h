#pragma once

#include <memory>

#include "../../common/random/include/RandomNumberGenerator.h"
#include "DictionaryWordRandomizer.h"

namespace glossary::dictionaryService
{
class DefaultDictionaryWordRandomizer : public DictionaryWordRandomizer
{
public:
    explicit DefaultDictionaryWordRandomizer(std::shared_ptr<common::RandomNumberGenerator>);

    DictionaryWord randomize(const DictionaryWords&) const override;

private:
    std::shared_ptr<common::RandomNumberGenerator> randomNumberGenerator;
    int getRandomIndex(DictionaryWords::size_type) const;
};
}