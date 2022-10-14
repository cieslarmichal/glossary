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
    DefaultWordDescriptionService(std::shared_ptr<wordDescriptionDownloader::WordDescriptionDownloader>,
                                  std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository>,
                                  std::unique_ptr<WordsApiConnectionChecker>, std::unique_ptr<ApiKeyReader>,
                                  std::unique_ptr<ApiKeyLocationUpdater>);

    wordDescriptionRepository::WordDescription
    retrieveWordDescription(const wordDescriptionRepository::std::string&) noexcept override;
    std::optional<wordDescriptionRepository::WordDescription>
    downloadWordDescription(const wordDescriptionRepository::std::string&) override;
    WordsApiStatus connectionToWordsApiAvailable() const override;
    void updateApiKeyLocation(const std::string& apiKeyLocation) override;

private:
    std::optional<wordDescriptionRepository::WordDescription>
    getWordDescriptionFromRepository(const wordDescriptionRepository::std::string& englishWord) const;
    std::optional<wordDescriptionRepository::WordDescription>
    downloadWordDescriptionFromDownloader(const wordDescriptionRepository::std::string& englishWord) const;
    wordDescriptionRepository::WordDescription
    getEmptyWordDescriptionWithEnglishWord(const wordDescriptionRepository::std::string& englishWord) const;
    void saveWordDescriptionInRepository(const wordDescriptionRepository::WordDescription&);

    std::shared_ptr<wordDescriptionDownloader::WordDescriptionDownloader> wordDescriptionDownloader;
    std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository> wordDescriptionRepository;
    std::unique_ptr<WordsApiConnectionChecker> connectionChecker;
    std::unique_ptr<ApiKeyReader> apiKeyReader;
    std::unique_ptr<ApiKeyLocationUpdater> apiKeyLocationUpdater;
    std::optional<std::string> wordsApiKey;
};
}