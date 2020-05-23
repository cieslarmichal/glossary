#include "DefaultWordDescriptionRetrieverService.h"

namespace glossary::wordDescriptionService
{
DefaultWordDescriptionRetrieverService::DefaultWordDescriptionRetrieverService(
    std::shared_ptr<wordDescriptionDownloader::WordDescriptionDownloader> downloader,
    std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository> repo)
    : wordDescriptionDownloader{std::move(downloader)}, wordDescriptionRepository{std::move(repo)}
{
}

wordDescriptionRepository::WordDescription DefaultWordDescriptionRetrieverService::retrieveWordDescription(
    const wordDescriptionRepository::EnglishWord& englishWord)
{
    if (const auto wordDescriptionFromRepository = getWordDescriptionFromRepository(englishWord))
    {
        return *wordDescriptionFromRepository;
    }

    if (const auto createdWordDescription = downloadWordDescription(englishWord))
    {
        saveWordDescriptionInRepository(*createdWordDescription);
        return *createdWordDescription;
    }

    const auto emptyWordDescriptionWithEnglishWord = getEmptyWordDescriptionWithEnglishWord(englishWord);
    saveWordDescriptionInRepository(emptyWordDescriptionWithEnglishWord);
    return emptyWordDescriptionWithEnglishWord;
}

boost::optional<wordDescriptionRepository::WordDescription>
DefaultWordDescriptionRetrieverService::getWordDescriptionFromRepository(
    const wordDescriptionRepository::EnglishWord& englishWord) const
{
    return wordDescriptionRepository->getWordDescription(englishWord);
}

boost::optional<wordDescriptionRepository::WordDescription>
DefaultWordDescriptionRetrieverService::downloadWordDescription(
    const wordDescriptionRepository::EnglishWord& englishWord) const
{
    return wordDescriptionDownloader->downloadWordDescription(englishWord);
}

void DefaultWordDescriptionRetrieverService::saveWordDescriptionInRepository(
    const wordDescriptionRepository::WordDescription& wordDescription)
{
    wordDescriptionRepository->addWordDescription(wordDescription);
}

wordDescriptionRepository::WordDescription
DefaultWordDescriptionRetrieverService::getEmptyWordDescriptionWithEnglishWord(
    const wordDescriptionRepository::EnglishWord& englishWord) const
{
    return wordDescriptionRepository::WordDescription{englishWord, {}, {}, {}};
}
}