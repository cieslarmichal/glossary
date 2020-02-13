#pragma once

#include "statisticsDb/Statistics.h"
#include "translationsDb/Translations.h"
#include "wordsDescriptionsDb/WordsDescriptions.h"

class WordsDb
{
public:
    virtual ~WordsDb() = default;

    virtual void addTranslation(translationsDb::Translation) = 0;
    virtual boost::optional<translationsDb::Translation>
    getTranslation(const PolishWord&) const = 0;
    virtual translationsDb::Translations getTranslations() const = 0;

    virtual void
    addWordDescription(const wordsDescriptionsDb::WordDescription&) const = 0;
    virtual boost::optional<wordsDescriptionsDb::WordDescription>
    getWordDescription(const EnglishWord&) const = 0;
    virtual wordsDescriptionsDb::WordsDescriptions
    getWordsDescriptions() const = 0;
    virtual bool containsWordDescription(const EnglishWord&) const = 0;

    virtual boost::optional<statisticsDb::WordStatistics>
    getWordStatistics(const EnglishWord&) const = 0;
    virtual statisticsDb::Statistics getStatistics() const = 0;
    virtual void addWordStatistics(statisticsDb::WordStatistics) = 0;
    virtual void addCorrectAnswer(const EnglishWord&) = 0;
    virtual void addIncorrectAnswer(const EnglishWord&) = 0;
    virtual void resetStatistics() = 0;
};
