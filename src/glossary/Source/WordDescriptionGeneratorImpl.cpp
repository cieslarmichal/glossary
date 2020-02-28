#include "WordDescriptionGeneratorImpl.h"

#include <iostream>

using namespace wordsDescriptionsDb;

WordDescriptionGeneratorImpl::WordDescriptionGeneratorImpl(std::unique_ptr<WordDescriptionService> service)
    : wordDescriptionService{std::move(service)}
{
}

WordsDescriptions
WordDescriptionGeneratorImpl::generateWordsDescriptions(const EnglishWords& englishWords) const
{
    WordsDescriptions wordsDescriptions;
    int wordDescriptionCounter = 0;
    for (const auto& englishWord : englishWords)
    {
        wordsDescriptions.emplace_back(generateWordDescription(englishWord));
        std::cout << "Downloading wordsDescriptions " << ++wordDescriptionCounter << "/"
                  << englishWords.size() << "\n";
    }
    return wordsDescriptions;
}

WordDescription WordDescriptionGeneratorImpl::generateWordDescription(const EnglishWord& englishWord) const
{
    if (const auto wordDescription = wordDescriptionService->getWordDescription(englishWord))
    {
        return *wordDescription;
    }
    return WordDescription{englishWord, {}};
}
