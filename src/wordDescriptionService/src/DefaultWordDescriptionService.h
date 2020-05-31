#pragma once

#include <memory>

#include "ApiKeyLocationUpdater.h"
#include "ApiKeyReader.h"
#include "WordDescriptionService.h"
#include "WordsApiConnectionChecker.h"
#include "wordDescriptionDownloader/WordDescriptionDownloader.h"
#include "wordDescriptionRepository/WordDescriptionRepository.h"

namespace glossary::wordDescriptionService
{
class DefaultWordDescriptionService : public WordDescriptionService
{
public:
    DefaultWordDescriptionService(
        std::shared_ptr<wordDescriptionDownloader::WordDescriptionDownloader>,
        std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository>,
        std::unique_ptr<WordsApiConnectionChecker>, std::unique_ptr<ApiKeyReader>,
        std::unique_ptr<ApiKeyLocationUpdater>);

    wordDescriptionRepository::WordDescription
    retrieveWordDescription(const wordDescriptionRepository::EnglishWord&) noexcept override;
    boost::optional<wordDescriptionRepository::WordDescription>
    downloadWordDescription(const wordDescriptionRepository::EnglishWord&) override;
    WordsApiStatus connectionToWordsApiAvailable() const override;
    void updateApiKeyLocation(const std::string& apiKeyLocation) override;

private:
    boost::optional<wordDescriptionRepository::WordDescription>
    getWordDescriptionFromRepository(const wordDescriptionRepository::EnglishWord& englishWord) const;
    boost::optional<wordDescriptionRepository::WordDescription>
    downloadWordDescriptionFromDownloader(const wordDescriptionRepository::EnglishWord& englishWord) const;
    wordDescriptionRepository::WordDescription
    getEmptyWordDescriptionWithEnglishWord(const wordDescriptionRepository::EnglishWord& englishWord) const;
    void saveWordDescriptionInRepository(const wordDescriptionRepository::WordDescription&);

    std::shared_ptr<wordDescriptionDownloader::WordDescriptionDownloader> wordDescriptionDownloader;
    std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository> wordDescriptionRepository;
    std::unique_ptr<WordsApiConnectionChecker> connectionChecker;
    std::unique_ptr<ApiKeyReader> apiKeyReader;
    std::unique_ptr<ApiKeyLocationUpdater> apiKeyLocationUpdater;
    boost::optional<std::string> wordsApiKey;
};
}