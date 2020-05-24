#include "DefaultWordDescriptionRetrieverService.h"

#include "webConnection/exceptions/ConnectionFailed.h"
#include "wordDescriptionDownloader/exceptions/InvalidApiKey.h"

namespace glossary::wordDescriptionService
{
DefaultWordDescriptionRetrieverService::DefaultWordDescriptionRetrieverService(
    std::shared_ptr<wordDescriptionDownloader::WordDescriptionDownloader> downloader,
    std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository> repo,
    std::unique_ptr<WordsApiConnectionChecker> checker)
    : wordDescriptionDownloader{std::move(downloader)},
      wordDescriptionRepository{std::move(repo)},
      connectionChecker{std::move(checker)}
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

    auto emptyWordDescriptionWithEnglishWord = getEmptyWordDescriptionWithEnglishWord(englishWord);
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
    try
    {
        return wordDescriptionDownloader->tryDownloadWordDescription(englishWord);
    }
    catch (const webConnection::exceptions::ConnectionFailed& e)
    {
        std::cerr << "Connection failed: " << e.what();
    }
    catch (const wordDescriptionDownloader::exceptions::InvalidApiKey& e)
    {
        std::cerr << "Invalid api key: " << e.what();
    }
    return boost::none;
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

WordsApiStatus DefaultWordDescriptionRetrieverService::connectionToWordsApiAvailable()
{
    return connectionChecker->connectionToWordsApiAvailable();
}
}