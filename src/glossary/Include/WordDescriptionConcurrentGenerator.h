#pragma once

#include <memory>

#include "WordDescriptionGenerator.h"
#include "WordDescriptionRetrieverService.h"
#include "utils/SupportedThreadsCalculator.h"
#include "utils/ThreadSafeQueue.h"

namespace glossary
{
class WordDescriptionConcurrentGenerator : public WordDescriptionGenerator
{
public:
    explicit WordDescriptionConcurrentGenerator(std::shared_ptr<WordDescriptionRetrieverService>);

    wordDescriptionRepository::WordsDescriptions
    generateWordsDescriptions(const wordDescriptionRepository::EnglishWords&) override;
    wordDescriptionRepository::WordDescription
    generateWordDescription(const wordDescriptionRepository::EnglishWord&) override;

private:
    unsigned getAmountOfThreads() const;
    void generatorWorker(utils::ThreadSafeQueue<wordDescriptionRepository::EnglishWord>& englishWords,
                         utils::ThreadSafeQueue<wordDescriptionRepository::WordDescription>&);

    std::shared_ptr<WordDescriptionRetrieverService> wordDescriptionRetrieverService;
    utils::SupportedThreadsCalculator supportedThreadsCalculator;
};
}