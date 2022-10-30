#include "GetWordDescriptionQueryImpl.h"

namespace glossary::dictionary
{
GetWordDescriptionQueryImpl::GetWordDescriptionQueryImpl(
    std::shared_ptr<WordDescriptionRepository> wordDescriptionRepositoryInit,
    std::unique_ptr<WordsApiClient> wordsApiClientInit)
    : wordDescriptionRepository{std::move(wordDescriptionRepositoryInit)}, wordsApiClient{std::move(wordsApiClientInit)}
{
}

WordDescription GetWordDescriptionQueryImpl::getWordDescription(const std::string& englishWord) const
{
    const auto cachedWordDescription = wordDescriptionRepository->getWordDescription(englishWord);

    if (cachedWordDescription)
    {
        return *cachedWordDescription;
    }

    const auto wordDefinitions = wordsApiClient->getWordDefinitions(englishWord);

    const auto wordExamples = wordsApiClient->getWordExamples(englishWord);

    const auto wordSynonyms = wordsApiClient->getWordSynonyms(englishWord);

    auto wordDescription = WordDescription{englishWord, wordDefinitions, wordExamples, wordSynonyms};

    wordDescriptionRepository->addWordDescription(wordDescription);

    return wordDescription;
}

}
