#pragma once

#include <memory>

#include "WordsDb.h"
#include "statisticsDb/StatisticsDb.h"
#include "translationsDb/TranslationsDb.h"
#include "wordsDescriptionsDb/WordsDescriptionsDb.h"

class WordsDbImpl : public WordsDb
{
public:
    WordsDbImpl(std::unique_ptr<translationsDb::TranslationsDb>,
                std::unique_ptr<wordsDescriptionsDb::WordsDescriptionsDb>,
                std::unique_ptr<statisticsDb::StatisticsDb>);

    void addTranslation(translationsDb::Translation) override;
    boost::optional<translationsDb::Translation>
    getTranslation(const PolishWord&) const override;
    translationsDb::Translations getTranslations() const override;

    void addWordDescription(
        const wordsDescriptionsDb::WordDescription&) const override;
    boost::optional<wordsDescriptionsDb::WordDescription>
    getWordDescription(const EnglishWord&) const override;
    wordsDescriptionsDb::WordsDescriptions
    getWordsDescriptions() const override;
    bool containsWordDescription(const EnglishWord&) const override;

    boost::optional<statisticsDb::WordStatistics>
    getWordStatistics(const EnglishWord&) const override;
    statisticsDb::Statistics getStatistics() const override;
    void addWordStatistics(statisticsDb::WordStatistics) override;
    void addCorrectAnswer(const EnglishWord&) override;
    void addIncorrectAnswer(const EnglishWord&) override;
    void resetStatistics() override;

private:
    std::unique_ptr<translationsDb::TranslationsDb> translationsDb;
    std::unique_ptr<wordsDescriptionsDb::WordsDescriptionsDb>
        wordsDescriptionsDb;
    std::unique_ptr<statisticsDb::StatisticsDb> statisticsDb;
};

