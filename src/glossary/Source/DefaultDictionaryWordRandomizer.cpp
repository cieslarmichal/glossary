#include "DefaultDictionaryWordRandomizer.h"

#include <random>
#include <stdexcept>

namespace glossary
{
DefaultDictionaryWordRandomizer::DefaultDictionaryWordRandomizer(
    std::shared_ptr<utils::RandomNumberGenerator> randomNumberGeneratorInit)
    : randomNumberGenerator{std::move(randomNumberGeneratorInit)}
{
}

dictionaryRepository::DictionaryWord
DefaultDictionaryWordRandomizer::randomize(const dictionaryRepository::DictionaryWords& dictionaryWords) const
{
    if (dictionaryWords.empty())
        throw std::invalid_argument{"Dictionary words are empty, cant randomize word"};
    return dictionaryWords.at(getRandomIndex(dictionaryWords.size()));
}

int DefaultDictionaryWordRandomizer::getRandomIndex(
    dictionaryRepository::DictionaryWords::size_type wordsAmount) const
{
    return randomNumberGenerator->generate(0, static_cast<int>(wordsAmount - 1));
}

}