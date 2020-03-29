#pragma once

#include <memory>

#include "SupportedThreadsCalculator.h"
#include "WordDescriptionGenerator.h"
#include "WordDescriptionRetrieverService.h"
#include "utils/ThreadSafeQueue.h"

class WordDescriptionConcurrentGenerator : public WordDescriptionGenerator
{
public:
    // TODO: refactor, make few classes from this class
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
    SupportedThreadsCalculator amountOfSupportedThreadsCalculator;
};