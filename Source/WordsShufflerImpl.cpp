#include "WordsShufflerImpl.h"

#include <algorithm>
#include <chrono>
#include <random>

WordsDescriptions
WordsShufflerImpl::shuffle(const WordsDescriptions& words) const
{
    if (not needToShuffle(words))
    {
        return words;
    }

    return shuffleWords(words);
}

WordsDescriptions
WordsShufflerImpl::shuffleWords(const WordsDescriptions& words) const
{
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    auto randomEngine = std::default_random_engine(seed);
    auto shuffledWords{words};

    while (shuffledWords == words)
    {
        std::shuffle(shuffledWords.begin(), shuffledWords.end(), randomEngine);
    }

    return shuffledWords;
}

bool WordsShufflerImpl::needToShuffle(const WordsDescriptions& words) const
{
    return words.size() >= 2;
}
