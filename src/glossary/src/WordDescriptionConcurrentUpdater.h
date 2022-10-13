#pragma once

#include <memory>

#include "../../common/collection/include/ThreadSafeQueue.h"
#include "../../common/concurrency/include/SupportedThreadsCalculator.h"
#include "dictionaryService/DictionaryObserver.h"
#include "wordDescriptionDownloader/WordDescriptionDownloader.h"
#include "wordDescriptionRepository/WordDescriptionRepository.h"
#include "wordDescriptionService/WordDescriptionService.h"

namespace glossary
{
class WordDescriptionConcurrentUpdater : public dictionaryService::DictionaryObserver
{
public:
    WordDescriptionConcurrentUpdater(std::shared_ptr<wordDescriptionService::WordDescriptionService>,
                                     std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository>);

    void update(const dictionaryService::EnglishWords&) override;

private:
    unsigned getAmountOfThreads() const;
    wordDescriptionRepository::EnglishWords
    getEnglishWordsWithoutWordDescription(const wordDescriptionRepository::EnglishWords&) const;
    void loadingWordDescriptionWorker(common::ThreadSafeQueue<wordDescriptionRepository::std::string>&,
                                      common::ThreadSafeQueue<wordDescriptionRepository::WordDescription>&);
    boost::optional<wordDescriptionRepository::WordDescription>
    downloadWordDescription(const wordDescriptionRepository::std::string&);
    void loadWordsDescriptionsIntoRepository(const wordDescriptionRepository::WordsDescriptions&);

    std::shared_ptr<wordDescriptionService::WordDescriptionService> wordDescriptionService;
    std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository> wordDescriptionRepository;
    common::SupportedThreadsCalculator supportedThreadsCalculator;
};
}