#include "WordsRandomizerImpl.h"

#include <algorithm>
#include <chrono>
#include <random>

Words WordsRandomizerImpl::randomize(const Words& words) const
{
    if(not needToShuffle(words))
    {
        return words;
    }

    return shuffleWords(words);
}

Words WordsRandomizerImpl::shuffleWords(const Words& words) const
{
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    auto randomEngine = std::default_random_engine(seed);
    auto shuffledWords{words};

    while(shuffledWords == words)
    {
        std::shuffle(shuffledWords.begin(), shuffledWords.end(), randomEngine);
    }

    return shuffledWords;
}

bool WordsRandomizerImpl::needToShuffle(const Words& words) const
{
    return words.size() >= 2;
}
