#pragma once

#include <memory>

#include "dictionaryService/DictionaryObserver.h"
#include "utils/SupportedThreadsCalculator.h"
#include "utils/ThreadSafeQueue.h"
#include "wordDescriptionDownloader/WordDescriptionDownloader.h"
#include "wordDescriptionRepository/WordDescriptionRepository.h"

namespace glossary
{
class WordDescriptionConcurrentUpdater : public dictionaryService::DictionaryObserver
{
public:
    WordDescriptionConcurrentUpdater(std::shared_ptr<wordDescriptionDownloader::WordDescriptionDownloader>,
                                     std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository>);

    void update(const dictionaryService::EnglishWords&) override;

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