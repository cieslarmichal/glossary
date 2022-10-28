#include "GetRandomWordFromDictionaryQueryImpl.h"

#include "exceptions/DictionaryMissingWordsError.h"
#include "exceptions/DictionaryNotFoundError.h"

namespace glossary::dictionary
{
GetRandomWordFromDictionaryQueryImpl::GetRandomWordFromDictionaryQueryImpl(
    std::shared_ptr<DictionaryRepository> dictionaryRepositoryInit,
    std::shared_ptr<common::random::RandomNumberGenerator> randomNumberGeneratorInit)
    : dictionaryRepository{std::move(dictionaryRepositoryInit)},
      randomNumberGenerator{std::move(randomNumberGeneratorInit)}
{
}

DictionaryWord GetRandomWordFromDictionaryQueryImpl::getRandomWord(const std::string& dictionaryName) const
{
    const auto dictionary = dictionaryRepository->getDictionary(dictionaryName);

    if (!dictionary)
    {
        throw exceptions::DictionaryNotFoundError{""};
    }

    if (dictionary->words.empty())
    {
        throw exceptions::DictionaryMissingWordsError{""};
    }

    const auto randomIndex = randomNumberGenerator->generate(0, static_cast<int>(dictionary->words.size() - 1));

    return dictionary->words.at(randomIndex);
}

}
