#pragma once

#include "translationsDb/Translations.h"
#include "wordsDescriptionsDb/WordsDescriptions.h"
#include "statisticsDb/Statistics.h"

namespace wordsDb
{

class WordsDb
{
public:
    virtual ~WordsDb() = default;

    virtual void addTranslation(Translation) = 0;
    virtual boost::optional<Translation>
    getTranslation(const PolishWord&) const = 0;
    virtual Translations getTranslations() const = 0;

    virtual void addWordDescription(const WordDescription&) const = 0;
    virtual boost::optional<WordDescription>
    getWordDescription(const EnglishWord&) const = 0;
    virtual WordsDescriptions getWordsDescriptions() const = 0;
    virtual bool contains(const EnglishWord&) const = 0;

    virtual boost::optional<WordStatistics>
    getWordStatistics(const EnglishWord&) const = 0;
    virtual Statistics getStatistics() const = 0;
    virtual void addWordStatistics(WordStatistics) = 0;
    virtual void addCorrectAnswer(const EnglishWord&) = 0;
    virtual void addIncorrectAnswer(const EnglishWord&) = 0;
    virtual void resetStatistics() = 0;
};
}