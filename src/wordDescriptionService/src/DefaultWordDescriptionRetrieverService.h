#pragma once

#include <memory>

#include "WordDescriptionRetrieverService.h"
#include "WordsApiConnectionChecker.h"
#include "wordDescriptionDownloader/WordDescriptionDownloader.h"
#include "wordDescriptionRepository/WordDescriptionRepository.h"

namespace glossary::wordDescriptionService
{
class DefaultWordDescriptionRetrieverService : public WordDescriptionRetrieverService
{
public:
    DefaultWordDescriptionRetrieverService(
        std::shared_ptr<wordDescriptionDownloader::WordDescriptionDownloader>,
        std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository>,
        std::unique_ptr<WordsApiConnectionChecker>);

    wordDescriptionRepository::WordDescription
    retrieveWordDescription(const wordDescriptionRepository::EnglishWord&) override;
    WordsApiStatus connectionToWordsApiAvailable() override;

private:
    boost::optional<wordDescriptionRepository::WordDescription>
    getWordDescriptionFromRepository(const wordDescriptionRepository::EnglishWord& englishWord) const;
    boost::optional<wordDescriptionRepository::WordDescription>
    downloadWordDescription(const wordDescriptionRepository::EnglishWord& englishWord) const;
    wordDescriptionRepository::WordDescription
    getEmptyWordDescriptionWithEnglishWord(const wordDescriptionRepository::EnglishWord& englishWord) const;
    void saveWordDescriptionInRepository(const wordDescriptionRepository::WordDescription&);

    std::shared_ptr<wordDescriptionDownloader::WordDescriptionDownloader> wordDescriptionDownloader;
    std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository> wordDescriptionRepository;
    std::unique_ptr<WordsApiConnectionChecker> connectionChecker;
};
}