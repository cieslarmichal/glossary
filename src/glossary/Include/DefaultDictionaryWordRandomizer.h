#pragma once

#include <memory>

#include "DictionaryWordRandomizer.h"
#include "utils/RandomNumberGenerator.h"

namespace glossary
{
class DefaultDictionaryWordRandomizer : public DictionaryWordRandomizer
{
public:
    explicit DefaultDictionaryWordRandomizer(std::shared_ptr<utils::RandomNumberGenerator>);

    dictionaryRepository::DictionaryWord
    randomize(const dictionaryRepository::DictionaryWords&) const override;

private:
    std::shared_ptr<utils::RandomNumberGenerator> randomNumberGenerator;
    int getRandomIndex(dictionaryRepository::DictionaryWords::size_type) const;
};
}