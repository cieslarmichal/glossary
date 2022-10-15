#pragma once

#include <memory>

#include "../../common/collection/include/ThreadSafeQueue.h"
#include "../../common/concurrency/include/SupportedThreadsCalculator.h"
#include "../../domain/dictionary/include/WordDescriptionDownloader.h"
#include "../../domain/dictionary/include/WordDescriptionRepository.h"
#include "dictionaryService/DictionaryObserver.h"
#include "wordDescriptionService/WordDescriptionService.h"

namespace glossary
{
class WordDescriptionConcurrentUpdater : public dictionary::DictionaryObserver
{
public:
    WordDescriptionConcurrentUpdater(std::shared_ptr<wordDescriptionService::WordDescriptionService>,
                                     std::shared_ptr<dictionary::WordDescriptionRepository>);

    void update(const dictionary::std::vector<std::string>&) override;

private:
    unsigned getAmountOfThreads() const;
    dictionary::std::vector<std::string>
    getEnglishWordsWithoutWordDescription(const dictionary::std::vector<std::string>&) const;
    void loadingWordDescriptionWorker(common::ThreadSafeQueue<std::string>&,
                                      common::ThreadSafeQueue<dictionary::WordDescription>&);
    std::optional<dictionary::WordDescription> downloadWordDescription(const std::string&);
    void loadWordsDescriptionsIntoRepository(const dictionary::WordsDescriptions&);

    std::shared_ptr<wordDescriptionService::WordDescriptionService> wordDescriptionService;
    std::shared_ptr<dictionary::WordDescriptionRepository> wordDescriptionRepository;
    common::SupportedThreadsCalculator supportedThreadsCalculator;
};
}