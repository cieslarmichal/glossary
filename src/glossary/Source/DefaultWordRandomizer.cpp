#include "DefaultWordRandomizer.h"

#include <random>
#include <stdexcept>

namespace glossary
{
DefaultWordRandomizer::DefaultWordRandomizer(
    std::shared_ptr<utils::RandomNumberGenerator> randomNumberGeneratorInit)
    : randomNumberGenerator{std::move(randomNumberGeneratorInit)}
{
}

Word DefaultWordRandomizer::randomizeWord(const Words& words) const
{
    if (words.empty())
        throw std::invalid_argument{"Words are empty, cant randomize word"};

    return words.at(getRandomIndex(words.size()));
}

Words::size_type DefaultWordRandomizer::getRandomIndex(Words::size_type wordsAmount) const
{
    return randomNumberGenerator->generate(0, static_cast<int>(wordsAmount-1));
}
}