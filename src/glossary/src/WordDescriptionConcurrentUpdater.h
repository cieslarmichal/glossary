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
class WordDescriptionConcurrentUpdater : public dictionary::DictionaryObserver
{
public:
    WordDescriptionConcurrentUpdater(std::shared_ptr<wordDescriptionService::WordDescriptionService>,
                                     std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository>);

    void update(const dictionary::std::vector<std::string>&) override;

private:
    unsigned getAmountOfThreads() const;
    wordDescriptionRepository::std::vector<std::string>
    getEnglishWordsWithoutWordDescription(const wordDescriptionRepository::std::vector<std::string>&) const;
    void loadingWordDescriptionWorker(common::ThreadSafeQueue<wordDescriptionRepository::std::string>&,
                                      common::ThreadSafeQueue<wordDescriptionRepository::WordDescription>&);
    std::optional<wordDescriptionRepository::WordDescription>
    downloadWordDescription(const wordDescriptionRepository::std::string&);
    void loadWordsDescriptionsIntoRepository(const wordDescriptionRepository::WordsDescriptions&);

    std::shared_ptr<wordDescriptionService::WordDescriptionService> wordDescriptionService;
    std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository> wordDescriptionRepository;
    common::SupportedThreadsCalculator supportedThreadsCalculator;
};
}