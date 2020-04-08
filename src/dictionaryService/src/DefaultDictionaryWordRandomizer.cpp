#include "DefaultDictionaryWordRandomizer.h"

#include <random>
#include <stdexcept>

namespace glossary::dictionaryService
{
DefaultDictionaryWordRandomizer::DefaultDictionaryWordRandomizer(
    std::shared_ptr<utils::RandomNumberGenerator> randomNumberGeneratorInit)
    : randomNumberGenerator{std::move(randomNumberGeneratorInit)}
{
}

DictionaryWord DefaultDictionaryWordRandomizer::randomize(const DictionaryWords& dictionaryWords) const
{
    if (dictionaryWords.empty())
        throw std::invalid_argument{"Dictionary words are empty, cant randomize word"};
    return dictionaryWords.at(getRandomIndex(dictionaryWords.size()));
}

int DefaultDictionaryWordRandomizer::getRandomIndex(DictionaryWords::size_type wordsAmount) const
{
    return randomNumberGenerator->generate(0, static_cast<int>(wordsAmount - 1));
}

}