#pragma once

#include <memory>

#include "DictionaryWordRandomizer.h"
#include "random/RandomNumberGenerator.h"

namespace glossary::dictionary
{
class DefaultDictionaryWordRandomizer : public DictionaryWordRandomizer
{
public:
    explicit DefaultDictionaryWordRandomizer(std::shared_ptr<common::random::RandomNumberGenerator>);

    DictionaryWord randomize(const std::vector<DictionaryWord>&) const override;

private:
    std::shared_ptr<common::random::RandomNumberGenerator> randomNumberGenerator;
    int getRandomIndex(std::vector<DictionaryWord>::size_type) const;
};
}