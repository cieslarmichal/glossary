#pragma once

#include <memory>

#include "WordDescriptionLoader.h"
#include "utils/SupportedThreadsCalculator.h"
#include "utils/ThreadSafeQueue.h"
#include "wordDescriptionDownloader/WordDescriptionDownloader.h"
#include "wordDescriptionRepository/WordDescriptionRepository.h"

namespace glossary
{
class WordDescriptionConcurrentLoader : public WordDescriptionLoader
{
public:
    WordDescriptionConcurrentLoader(std::shared_ptr<wordDescriptionDownloader::WordDescriptionDownloader>,
                                    std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository>);

    void loadMissingWordsDescriptions(const wordDescriptionRepository::EnglishWords&) override;

private:
    unsigned getAmountOfThreads() const;
    wordDescriptionRepository::EnglishWords
    getEnglishWordsWithoutWordDescription(const wordDescriptionRepository::EnglishWords&) const;
    void loadingWordDescriptionWorker(utils::ThreadSafeQueue<wordDescriptionRepository::EnglishWord>&,
                                      utils::ThreadSafeQueue<wordDescriptionRepository::WordDescription>&);
    boost::optional<wordDescriptionRepository::WordDescription>
    downloadWordDescription(const wordDescriptionRepository::EnglishWord&);
    void loadWordsDescriptionsIntoRepository(const wordDescriptionRepository::WordsDescriptions&);

    std::shared_ptr<wordDescriptionDownloader::WordDescriptionDownloader> wordDescriptionDownloader;
    std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository> wordDescriptionRepository;
    utils::SupportedThreadsCalculator supportedThreadsCalculator;
};
}