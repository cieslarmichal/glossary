#include "DefaultWordDescriptionService.h"

DefaultWordDescriptionService::DefaultWordDescriptionService(
    std::unique_ptr<wordDescriptionDownloader::WordDescriptionDownloader> downloader,
    std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository> db)
    : wordDescriptionDownloader{std::move(downloader)}, wordsDescriptionsDb{std::move(db)}
{
}

boost::optional<wordDescriptionRepository::WordDescription>
DefaultWordDescriptionService::getWordDescription(const wordDescriptionRepository::EnglishWord& englishWord)
{
    if (const auto wordDescriptionFromDb = getWordDescriptionFromDb(englishWord))
    {
        return wordDescriptionFromDb;
    }

    if (const auto createdWordDescription = createWordDescriptionFromHttp(englishWord))
    {
        saveWordDescriptionInDb(*createdWordDescription);
        return createdWordDescription;
    }
    return boost::none;
}

boost::optional<wordDescriptionRepository::WordDescription> DefaultWordDescriptionService::getWordDescriptionFromDb(
    const wordDescriptionRepository::EnglishWord& englishWord) const
{
    return wordsDescriptionsDb->getWordDescription(englishWord);
}

boost::optional<wordDescriptionRepository::WordDescription>
DefaultWordDescriptionService::createWordDescriptionFromHttp(
    const wordDescriptionRepository::EnglishWord& englishWord) const
{
    return wordDescriptionDownloader->downloadWordDescription(englishWord);
}

void DefaultWordDescriptionService::saveWordDescriptionInDb(
    const wordDescriptionRepository::WordDescription& wordDescription)
{
    wordsDescriptionsDb->addWordDescription(wordDescription);
}