#include "WordRandomizerImpl.h"

#include <random>
#include <stdexcept>

WordDescription
WordRandomizerImpl::randomizeWord(const WordsDescriptions& words) const
{
    if (words.empty())
    {
        throw std::runtime_error{"Cant randomize word"};
    }

    return words.at(getRandomIndex(words.size()));
}

WordsDescriptions::size_type
WordRandomizerImpl::getRandomIndex(WordsDescriptions::size_type size) const
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, int(size) - 1);
    return WordsDescriptions::size_type(dist(mt));
}
