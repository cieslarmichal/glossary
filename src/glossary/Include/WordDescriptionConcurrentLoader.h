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

    void loadWordsDescriptions(const wordDescriptionRepository::EnglishWords&) override;

private:
    void loadingWordDescriptionWorker(
        utils::ThreadSafeQueue<wordDescriptionRepository::EnglishWord>& englishWords);
    void loadWordDescription(const wordDescriptionRepository::EnglishWord&);
    unsigned getAmountOfThreads() const;

    std::shared_ptr<wordDescriptionDownloader::WordDescriptionDownloader> wordDescriptionDownloader;
    std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository> wordDescriptionRepository;
    utils::SupportedThreadsCalculator supportedThreadsCalculator;
};
}