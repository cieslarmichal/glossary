#include "WordDescriptionConcurrentGenerator.h"

#include <iostream>
#include <thread>

using namespace wordsDescriptionsDb;

WordDescriptionConcurrentGenerator::WordDescriptionConcurrentGenerator(std::unique_ptr<WordDescriptionService> service)
    : wordDescriptionService{std::move(service)}
{
}

WordsDescriptions
WordDescriptionConcurrentGenerator::generateWordsDescriptions(const EnglishWords& englishWords)
{
    utils::ThreadSafeQueue<EnglishWord> englishWordsQueue{englishWords};
    utils::ThreadSafeQueue<WordDescription> wordsDescriptions;

    std::thread t1(&WordDescriptionConcurrentGenerator::generatorWorker, this, std::ref(englishWordsQueue),
                   std::ref(wordsDescriptions));
    std::thread t2(&WordDescriptionConcurrentGenerator::generatorWorker, this, std::ref(englishWordsQueue),
                   std::ref(wordsDescriptions));
    std::thread t3(&WordDescriptionConcurrentGenerator::generatorWorker, this, std::ref(englishWordsQueue),
                   std::ref(wordsDescriptions));
    t1.join();
    t2.join();
    t3.join();

    return wordsDescriptions.popAll();

    //    WordsDescriptions wordsDescriptions;
    //    int wordDescriptionCounter = 0;
    //    for (const auto& englishWord : englishWords)
    //    {
    //        wordsDescriptions.emplace_back(generateWordDescription(englishWord));
    //        wordDescriptionCounter++;
    //        std::cout << "Generating wordsDescriptions " << wordDescriptionCounter << "/" <<
    //        englishWords.size()
    //                  << "\n";
    //    }
    //    return wordsDescriptions;
}

WordDescription WordDescriptionConcurrentGenerator::generateWordDescription(const EnglishWord& englishWord)
{
    if (const auto wordDescription = wordDescriptionService->getWordDescription(englishWord))
    {
        return *wordDescription;
    }
    return WordDescription{englishWord, {}};
}

void WordDescriptionConcurrentGenerator::generatorWorker(
    utils::ThreadSafeQueue<wordsDescriptionsDb::EnglishWord>& englishWords,
    utils::ThreadSafeQueue<wordsDescriptionsDb::WordDescription>& wordsDescriptions)
{
    std::cerr<<"THREAD ID: "<<std::this_thread::get_id()<<std::endl;
    while (not englishWords.empty())
    {
        if (const auto currentEnglishWord = englishWords.pop())
        {
            const auto generatedWordDescription = generateWordDescription(*currentEnglishWord);
            wordsDescriptions.push(generatedWordDescription);
        }
    }
}
