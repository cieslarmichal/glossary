#include "DefaultWordDescriptionService.h"

DefaultWordDescriptionService::DefaultWordDescriptionService(
    std::unique_ptr<wordDescriptionDownloader::WordDescriptionDownloader> downloader,
    std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository> repo)
    : wordDescriptionDownloader{std::move(downloader)}, wordDescriptionRepository{std::move(repo)}
{
}

boost::optional<wordDescriptionRepository::WordDescription>
DefaultWordDescriptionService::getWordDescription(const wordDescriptionRepository::EnglishWord& englishWord)
{
    if (const auto wordDescriptionFromDb = getWordDescriptionFromRepository(englishWord))
    {
        return wordDescriptionFromDb;
    }

    if (const auto createdWordDescription = downloadWordDescription(englishWord))
    {
        saveWordDescriptionInRepository(*createdWordDescription);
        return createdWordDescription;
    }
    return boost::none;
}

boost::optional<wordDescriptionRepository::WordDescription> DefaultWordDescriptionService::getWordDescriptionFromRepository(
    const wordDescriptionRepository::EnglishWord& englishWord) const
{
    return wordDescriptionRepository->getWordDescription(englishWord);
}

boost::optional<wordDescriptionRepository::WordDescription>
DefaultWordDescriptionService::downloadWordDescription(
    const wordDescriptionRepository::EnglishWord& englishWord) const
{
    return wordDescriptionDownloader->downloadWordDescription(englishWord);
}

void DefaultWordDescriptionService::saveWordDescriptionInRepository(
    const wordDescriptionRepository::WordDescription& wordDescription)
{
    wordDescriptionRepository->addWordDescription(wordDescription);
}