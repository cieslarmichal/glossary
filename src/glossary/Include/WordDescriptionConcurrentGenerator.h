#pragma once

#include <memory>

#include "WordDescriptionGenerator.h"
#include "WordDescriptionService.h"
#include "utils/ThreadSafeQueue.h"

class WordDescriptionConcurrentGenerator : public WordDescriptionGenerator
{
public:
    explicit WordDescriptionConcurrentGenerator(std::unique_ptr<WordDescriptionService>);

    wordDescriptionRepository::WordsDescriptions
    generateWordsDescriptions(const wordDescriptionRepository::EnglishWords&) override;
    wordDescriptionRepository::WordDescription
    generateWordDescription(const wordDescriptionRepository::EnglishWord&) override;

private:
    unsigned getAmountOfThreads() const;
    void generatorWorker(utils::ThreadSafeQueue<wordDescriptionRepository::EnglishWord>& englishWords,
                         utils::ThreadSafeQueue<wordDescriptionRepository::WordDescription>&);

    std::unique_ptr<WordDescriptionService> wordDescriptionService;
};