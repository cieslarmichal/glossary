#include "DefaultWordDescriptionService.h"

#include "httpClient/exceptions/ConnectionFailed.h"
#include "wordDescriptionDownloader/exceptions/InvalidApiKey.h"

namespace glossary::wordDescriptionService
{
DefaultWordDescriptionService::DefaultWordDescriptionService(
    std::shared_ptr<wordDescriptionDownloader::WordDescriptionDownloader> downloader,
    std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository> repo,
    std::unique_ptr<WordsApiConnectionChecker> checker, std::unique_ptr<ApiKeyReader> keyReader,
    std::unique_ptr<ApiKeyLocationUpdater> keyLocationUpdater)
    : wordDescriptionDownloader{std::move(downloader)},
      wordDescriptionRepository{std::move(repo)},
      connectionChecker{std::move(checker)},
      apiKeyReader{std::move(keyReader)},
      apiKeyLocationUpdater{std::move(keyLocationUpdater)},
      wordsApiKey{apiKeyReader->readApiKey()}
{
}

wordDescriptionRepository::WordDescription DefaultWordDescriptionService::retrieveWordDescription(
    const wordDescriptionRepository::std::string& englishWord) noexcept
{
    if (const auto wordDescriptionFromRepository = getWordDescriptionFromRepository(englishWord))
    {
        return *wordDescriptionFromRepository;
    }

    if (const auto createdWordDescription = downloadWordDescriptionFromDownloader(englishWord))
    {
        saveWordDescriptionInRepository(*createdWordDescription);
        return *createdWordDescription;
    }

    auto emptyWordDescriptionWithEnglishWord = getEmptyWordDescriptionWithEnglishWord(englishWord);
    if (wordsApiKey)
    {
        saveWordDescriptionInRepository(emptyWordDescriptionWithEnglishWord);
    }
    return emptyWordDescriptionWithEnglishWord;
}

std::optional<wordDescriptionRepository::WordDescription>
DefaultWordDescriptionService::downloadWordDescription(
    const wordDescriptionRepository::std::string& englishWord)
{
    return downloadWordDescriptionFromDownloader(englishWord);
}

std::optional<wordDescriptionRepository::WordDescription>
DefaultWordDescriptionService::getWordDescriptionFromRepository(
    const wordDescriptionRepository::std::string& englishWord) const
{
    return wordDescriptionRepository->getWordDescription(englishWord);
}

std::optional<wordDescriptionRepository::WordDescription>
DefaultWordDescriptionService::downloadWordDescriptionFromDownloader(
    const wordDescriptionRepository::std::string& englishWord) const
{
    if (not wordsApiKey)
    {
        return std::nullopt;
    }

    try
    {
        return wordDescriptionDownloader->tryDownloadWordDescription(englishWord, *wordsApiKey);
    }
    catch (const common::httpClient::exceptions::ConnectionFailed& e)
    {
        std::cerr << "Connection failed: " << e.what();
    }
    catch (const wordDescriptionDownloader::exceptions::InvalidApiKey& e)
    {
        std::cerr << "Invalid api key: " << e.what();
    }
    return std::nullopt;
}

void DefaultWordDescriptionService::saveWordDescriptionInRepository(
    const wordDescriptionRepository::WordDescription& wordDescription)
{
    wordDescriptionRepository->addWordDescription(wordDescription);
}

wordDescriptionRepository::WordDescription
DefaultWordDescriptionService::getEmptyWordDescriptionWithEnglishWord(
    const wordDescriptionRepository::std::string& englishWord) const
{
    return wordDescriptionRepository::WordDescription{englishWord, {}, {}, {}};
}

WordsApiStatus DefaultWordDescriptionService::connectionToWordsApiAvailable() const
{
    if (wordsApiKey)
    {
        return connectionChecker->connectionToWordsApiAvailable(*wordsApiKey);
    }
    return WordsApiStatus::InvalidApiKey;
}

void DefaultWordDescriptionService::updateApiKeyLocation(const std::string& apiKeyLocation)
{
    apiKeyLocationUpdater->updateApiKeyLocation(apiKeyLocation);
    wordsApiKey = apiKeyReader->readApiKey();
}

}