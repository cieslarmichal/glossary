#pragma once

#include <memory>

#include "WordDescriptionGenerator.h"
#include "WordDescriptionService.h"

class WordDescriptionGeneratorImpl : public WordDescriptionGenerator
{
public:
    WordDescriptionGeneratorImpl(std::unique_ptr<WordDescriptionService>);

    wordsDescriptionsDb::WordDescription generateWordDescription(
        const wordsDescriptionsDb::EnglishWord&) const override;
    wordsDescriptionsDb::WordsDescriptions generateWordsDescriptions(
        const wordsDescriptionsDb::EnglishWords&) const override;

private:
    std::unique_ptr<WordDescriptionService> wordDescriptionService;
};