#include "wordsDb/WordsDbImpl.h"

namespace wordsDb
{

WordsDbImpl::WordsDbImpl(
    std::unique_ptr<translationsDb::TranslationsDb> translationDbInit,
    std::unique_ptr<wordsDescriptionsDb::WordsDescriptionsDb>
        wordsDDescriptionsDbInit,
    std::unique_ptr<statisticsDb::StatisticsDb> statisticsDbInit)
    : translationsDb{std::move(translationDbInit)},
      wordsDescriptionsDb{std::move(wordsDDescriptionsDbInit)},
      statisticsDb{std::move(statisticsDbInit)}
{
}

void WordsDbImpl::addTranslation(translationsDb::Translation translation)
{
    translationsDb->addTranslation(std::move(translation));
}

boost::optional<translationsDb::Translation>
WordsDbImpl::getTranslation(const PolishWord& polishWord) const
{
    return translationsDb->getTranslation(polishWord);
}

translationsDb::Translations WordsDbImpl::getTranslations() const
{
    return translationsDb->getTranslations();
}

void WordsDbImpl::addWordDescription(
    const wordsDescriptionsDb::WordDescription& wordDescription) const
{
    wordsDescriptionsDb->addWordDescription(wordDescription);
}

boost::optional<wordsDescriptionsDb::WordDescription>
WordsDbImpl::getWordDescription(const EnglishWord& englishWord) const {
    return wordsDescriptionsDb->getWordDescription(englishWord);
}

wordsDescriptionsDb::WordsDescriptions WordsDbImpl::getWordsDescriptions() const
{
    return wordsDescriptionsDb->getWordsDescriptions();
}

bool WordsDbImpl::containsWordDescription(const EnglishWord& englishWord) const
{
    return wordsDescriptionsDb->contains(englishWord);
}

boost::optional<statisticsDb::WordStatistics>
WordsDbImpl::getWordStatistics(const EnglishWord& englishWord) const
{
    return statisticsDb->getWordStatistics(englishWord);
}

statisticsDb::Statistics WordsDbImpl::getStatistics() const
{
    return statisticsDb->getStatistics();
}

void WordsDbImpl::addWordStatistics(statisticsDb::WordStatistics wordStatistics)
{
    statisticsDb->addWordStatistics(wordStatistics);
}

void WordsDbImpl::addCorrectAnswer(const EnglishWord& englishWord)
{
    statisticsDb->addCorrectAnswer(englishWord);
}

void WordsDbImpl::addIncorrectAnswer(const EnglishWord& englishWord)
{
    statisticsDb->addIncorrectAnswer(englishWord);
}

void WordsDbImpl::resetStatistics()
{
    statisticsDb->resetStatistics();
}

}