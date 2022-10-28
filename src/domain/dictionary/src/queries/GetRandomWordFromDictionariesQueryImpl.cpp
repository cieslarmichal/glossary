#include "GetRandomWordFromDictionariesQueryImpl.h"

#include "exceptions/DictionaryMissingWordsError.h"

namespace glossary::dictionary
{
GetRandomWordFromDictionariesQueryImpl::GetRandomWordFromDictionariesQueryImpl(
    std::shared_ptr<DictionaryRepository> dictionaryRepositoryInit,
    std::shared_ptr<common::random::RandomNumberGenerator> randomNumberGeneratorInit)
    : dictionaryRepository{std::move(dictionaryRepositoryInit)},
      randomNumberGenerator{std::move(randomNumberGeneratorInit)}
{
}

DictionaryWord GetRandomWordFromDictionariesQueryImpl::getRandomWord() const
{
    const auto dictionaries = dictionaryRepository->getDictionaries();

    std::vector<DictionaryWord> allDictionariesWords;

    for (const auto& dictionary : dictionaries)
    {
        const auto& dictionaryWords = dictionary.words;

        allDictionariesWords.insert(allDictionariesWords.end(), dictionaryWords.begin(), dictionaryWords.end());
    }

    if (allDictionariesWords.empty())
    {
        throw exceptions::DictionaryMissingWordsError{""};
    }

    const auto randomIndex = randomNumberGenerator->generate(0, static_cast<int>(allDictionariesWords.size() - 1));

    return allDictionariesWords.at(randomIndex);
}

}
