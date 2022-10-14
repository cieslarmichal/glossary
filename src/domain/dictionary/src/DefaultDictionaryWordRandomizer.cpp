#include "DefaultDictionaryWordRandomizer.h"

#include <random>
#include <stdexcept>

namespace glossary::dictionary
{
DefaultDictionaryWordRandomizer::DefaultDictionaryWordRandomizer(
    std::shared_ptr<common::random::RandomNumberGenerator> randomNumberGeneratorInit)
    : randomNumberGenerator{std::move(randomNumberGeneratorInit)}
{
}

DictionaryWord
DefaultDictionaryWordRandomizer::randomize(const std::vector<DictionaryWord>& dictionaryWords) const
{
    if (dictionaryWords.empty())
        throw std::invalid_argument{"Dictionary words are empty, cant randomize word"};
    return dictionaryWords.at(getRandomIndex(dictionaryWords.size()));
}

int DefaultDictionaryWordRandomizer::getRandomIndex(std::vector<DictionaryWord>::size_type wordsAmount) const
{
    return randomNumberGenerator->generate(0, static_cast<int>(wordsAmount - 1));
}

}