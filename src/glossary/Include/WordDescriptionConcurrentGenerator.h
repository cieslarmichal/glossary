#pragma once

#include <memory>

#include "WordDescriptionGenerator.h"
#include "WordDescriptionService.h"
#include "utils/ThreadSafeQueue.h"

class WordDescriptionConcurrentGenerator : public WordDescriptionGenerator
{
public:
    explicit WordDescriptionConcurrentGenerator(std::unique_ptr<WordDescriptionService>);

    wordsDescriptionsDb::WordDescription
    generateWordDescription(const wordsDescriptionsDb::EnglishWord&) override;
    wordsDescriptionsDb::WordsDescriptions
    generateWordsDescriptions(const wordsDescriptionsDb::EnglishWords&) override;

private:
    void generatorWorker(utils::ThreadSafeQueue<wordsDescriptionsDb::EnglishWord>& englishWords,
                         utils::ThreadSafeQueue<wordsDescriptionsDb::WordDescription>&);

    std::unique_ptr<WordDescriptionService> wordDescriptionService;
};