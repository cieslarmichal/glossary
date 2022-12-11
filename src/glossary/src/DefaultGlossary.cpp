#include "DefaultGlossary.h"

#include <iostream>
#include <utility>

#include "collection/StlOperators.h"
#include "collection/StringHelper.h"
#include "dictionary/Dictionary.h"
#include "fileSystem/GetProjectPath.h"
#include "translation/Language.h"

namespace glossary
{

DefaultGlossary::DefaultGlossary(
    std::unique_ptr<DictionaryStatisticsCounter> counterInit,
    std::unique_ptr<dictionary::AddWordToDictionaryCommand> addWordToDictionaryCommandInit,
    std::unique_ptr<dictionary::CreateDictionaryCommand> createDictionaryCommandInit,
    std::unique_ptr<dictionary::RemoveDictionaryCommand> removeDictionaryCommandInit,
    std::unique_ptr<dictionary::CreateDictionaryFromCsvFileCommand> createDictionaryFromCsvFileCommandInit,
    std::unique_ptr<dictionary::RemoveWordFromDictionaryCommand> removeWordFromDictionaryCommandInit,
    std::unique_ptr<dictionary::UpdateWordTranslationInDictionaryCommand> updateWordTranslationInDictionaryCommandInit,
    std::unique_ptr<dictionary::GetDictionariesEnglishWordsQuery> getDictionariesEnglishWordsQueryInit,
    std::unique_ptr<dictionary::GetDictionariesNamesQuery> getDictionariesNamesQueryInit,
    std::unique_ptr<dictionary::GetDictionariesQuery> getDictionariesQueryInit,
    std::unique_ptr<dictionary::GetDictionaryEnglishWordsQuery> getDictionaryEnglishWordsQueryInit,
    std::unique_ptr<dictionary::GetDictionaryQuery> getDictionaryQueryInit,
    std::unique_ptr<dictionary::GetRandomWordFromDictionariesQuery> getRandomWordFromDictionariesQueryInit,
    std::unique_ptr<dictionary::GetRandomWordFromDictionaryQuery> getRandomWordFromDictionaryQueryInit,
    std::unique_ptr<dictionary::GetWordDescriptionQuery> getWordDescriptionQueryInit,
    std::unique_ptr<statistics::AddCorrectAnswerCommand> addCorrectAnswerCommandInit,
    std::unique_ptr<statistics::AddIncorrectAnswerCommand> addIncorrectAnswerCommandInit,
    std::unique_ptr<statistics::AddWordStatisticsCommand> addWordStatisticsCommandInit,
    std::unique_ptr<statistics::ResetWordsStatisticsCommand> resetWordsStatisticsCommandInit,
    std::unique_ptr<statistics::GetWordsStatisticsQuery> getWordsStatisticsQueryInit,
    std::unique_ptr<translation::GetTranslationQuery> getTranslationQueryInit,
    std::unique_ptr<translation::GetSupportedLanguagesQuery> getSupportedLanguagesQueryInit)
    : dictionaryStatisticsCounter{std::move(counterInit)},
      addWordToDictionaryCommand{std::move(addWordToDictionaryCommandInit)},
      createDictionaryCommand{std::move(createDictionaryCommandInit)},
      removeDictionaryCommand{std::move(removeDictionaryCommandInit)},
      createDictionaryFromCsvFileCommand{std::move(createDictionaryFromCsvFileCommandInit)},
      removeWordFromDictionaryCommand{std::move(removeWordFromDictionaryCommandInit)},
      updateWordTranslationInDictionaryCommand{std::move(updateWordTranslationInDictionaryCommandInit)},
      getDictionariesEnglishWordsQuery{std::move(getDictionariesEnglishWordsQueryInit)},
      getDictionariesNamesQuery{std::move(getDictionariesNamesQueryInit)},
      getDictionariesQuery{std::move(getDictionariesQueryInit)},
      getDictionaryEnglishWordsQuery{std::move(getDictionaryEnglishWordsQueryInit)},
      getDictionaryQuery{std::move(getDictionaryQueryInit)},
      getRandomWordFromDictionariesQuery{std::move(getRandomWordFromDictionariesQueryInit)},
      getRandomWordFromDictionaryQuery{std::move(getRandomWordFromDictionaryQueryInit)},
      getWordDescriptionQuery{std::move(getWordDescriptionQueryInit)},
      addCorrectAnswerCommand{std::move(addCorrectAnswerCommandInit)},
      addIncorrectAnswerCommand{std::move(addIncorrectAnswerCommandInit)},
      addWordStatisticsCommand{std::move(addWordStatisticsCommandInit)},
      resetWordsStatisticsCommand{std::move(resetWordsStatisticsCommandInit)},
      getWordsStatisticsQuery{std::move(getWordsStatisticsQueryInit)},
      getTranslationQuery{std::move(getTranslationQueryInit)},
      getSupportedLanguagesQuery{std::move(getSupportedLanguagesQueryInit)}
{
}

std::optional<std::string> DefaultGlossary::getRandomPolishWord() const
{
    try
    {
        const auto dictionaryWord = getRandomWordFromDictionariesQuery->getRandomWord();

        if (not dictionaryWord->translation)
        {
            return getTranslationQuery->getTranslation(
                {dictionaryWord->englishWord, translation::Language::English, translation::Language::Polish});
        }

        return dictionaryWord->translation;
    }
    catch (const std::runtime_error& error)
    {
        std::cerr << error.what();

        return std::nullopt;
    }
}

std::optional<std::string> DefaultGlossary::getRandomPolishWord(const std::string& dictionaryName) const
{
    try
    {
        auto dictionaryWord = getRandomWordFromDictionaryQuery->getRandomWord(dictionaryName);

        if (not dictionaryWord->translation)
        {
            return getTranslationQuery->getTranslation(
                {dictionaryWord->englishWord, translation::Language::English, translation::Language::Polish});
        }

        return dictionaryWord->translation;
    }
    catch (const std::runtime_error& error)
    {
        std::cerr << error.what();

        return std::nullopt;
    }
}

bool DefaultGlossary::verifyPolishWordTranslation(const std::string& polishWord, const std::string& englishWord) const
{
    const auto englishTranslationFromPolishWord = getTranslationQuery->getTranslation(
        {polishWord, translation::Language::Polish, translation::Language::English});

    if (englishTranslationFromPolishWord == std::nullopt)
    {
        return false;
    }

    if (common::collection::compareCaseInsensitive(*englishTranslationFromPolishWord, englishWord))
    {
        addCorrectAnswerCommand->addCorrectAnswer(englishWord);

        return true;
    }

    addIncorrectAnswerCommand->addIncorrectAnswer(*englishTranslationFromPolishWord);

    return false;
}

std::vector<dictionary::Dictionary> DefaultGlossary::getDictionaries() const
{
    return getDictionariesQuery->getDictionaries();
}

std::vector<std::string> DefaultGlossary::getDictionariesNames() const
{
    return getDictionariesNamesQuery->getDictionariesNames();
}

std::vector<dictionary::DictionaryWord> DefaultGlossary::getDictionaryWords(const std::string& dictionaryName) const
{
    const auto dictionary = getDictionaryQuery->getDictionary(dictionaryName);

    if (!dictionary)
    {
        return {};
    }

    return dictionary->words;
}

void DefaultGlossary::addDictionary(const std::string& dictionaryName) const
{
    createDictionaryCommand->createDictionary(dictionaryName);
}

void DefaultGlossary::removeDictionary(const std::string& dictionaryName) const
{
    removeDictionaryCommand->removeDictionary(dictionaryName);
}

void DefaultGlossary::addEnglishWordToDictionary(const std::string& englishWord,
                                                 const std::string& dictionaryName) const
{
    addWordToDictionaryCommand->addWordToDictionary(dictionaryName, {englishWord, std::nullopt});
}

void DefaultGlossary::addEnglishWordToDictionary(const std::string& englishWord, const std::string& translation,
                                                 const std::string& dictionaryName) const
{
    addWordToDictionaryCommand->addWordToDictionary(dictionaryName, {englishWord, translation});
}

void DefaultGlossary::removeEnglishWordFromDictionary(const std::string& englishWord,
                                                      const std::string& dictionaryName) const
{
    removeWordFromDictionaryCommand->removeWordFromDictionary(dictionaryName, englishWord);
}

void DefaultGlossary::addDictionaryFromFile(const std::string& dictionaryName,
                                            const std::string& pathToFileWithDictionaryWords) const
{
    createDictionaryFromCsvFileCommand->createDictionaryFromCsvFile(dictionaryName, pathToFileWithDictionaryWords);
}

void DefaultGlossary::updateDictionaryWordTranslationManually(const std::string& dictionaryName,
                                                              const std::string& englishWord,
                                                              const std::string& newTranslation) const
{
    updateWordTranslationInDictionaryCommand->updateWordTranslation(dictionaryName, englishWord, newTranslation);
}

void DefaultGlossary::updateDictionaryWordTranslationAutomatically(const std::string& dictionaryName,
                                                                   const std::string& englishWord) const
{
    const auto translation = getTranslationQuery->getTranslation(
        {englishWord, translation::Language::English, translation::Language::Polish});

    if (translation)
    {
        updateWordTranslationInDictionaryCommand->updateWordTranslation(dictionaryName, englishWord, *translation);
    }
}

void DefaultGlossary::updateDictionaryTranslationsAutomatically(const std::string& dictionaryName) const
{
    const auto dictionary = getDictionaryQuery->getDictionary(dictionaryName);

    if (dictionary)
    {
        for (const auto& dictionaryWord : dictionary->words)
        {
            if (dictionaryWord.translation && dictionaryWord.translation->empty())
            {
                updateDictionaryWordTranslation(dictionaryWord.englishWord, dictionaryName);
            }
        }
    }
}

dictionary::WordDescription DefaultGlossary::getEnglishWordDescription(const std::string& englishWord) const
{
    return getWordDescriptionQuery->getWordDescription(englishWord);
}

std::vector<std::string> DefaultGlossary::getSupportedTranslatorLanguages() const
{
    return getSupportedLanguagesQuery->getSupportedLanguages();
}

std::optional<std::string> DefaultGlossary::translate(const std::string& textToTranslate,
                                                      const std::string& sourceLanguageText,
                                                      const std::string& targetLanguageText) const
{
    translation::Language sourceLanguage;

    if (common::collection::compareCaseInsensitive(sourceLanguageText, "Polish"))
    {
        sourceLanguage = translation::Language::Polish;
    }
    else if (common::collection::compareCaseInsensitive(sourceLanguageText, "English"))
    {
        sourceLanguage = translation::Language::English;
    }
    else
    {
        std::cerr << "Invalid source language\n";
        return std::nullopt;
    }

    translation::Language targetLanguage;

    if (common::collection::compareCaseInsensitive(targetLanguageText, "Polish"))
    {
        targetLanguage = translation::Language::Polish;
    }
    else if (common::collection::compareCaseInsensitive(targetLanguageText, "English"))
    {
        targetLanguage = translation::Language::English;
    }
    else
    {
        std::cerr << "Invalid target language\n";
        return std::nullopt;
    }

    return getTranslationQuery->getTranslation({textToTranslate, sourceLanguage, targetLanguage});
}

std::optional<DictionaryStatistics> DefaultGlossary::getDictionaryStatistics(const std::string& dictionaryName) const
{
    const auto dictionary = getDictionaryQuery->getDictionary(dictionaryName);

    if (!dictionary)
    {
        return std::nullopt;
    }

    auto statistics = getWordsStatisticsQuery->getWordsStatistics();

    return dictionaryStatisticsCounter->countDictionaryStatistics(*dictionary, statistics);
}

DictionariesStatistics DefaultGlossary::getDictionariesStatistics() const
{
    auto dictionaries = getDictionariesQuery->getDictionaries();

    auto statistics = getWordsStatisticsQuery->getWordsStatistics();

    return dictionaryStatisticsCounter->countDictionariesStatistics(dictionaries, statistics);
}

void DefaultGlossary::resetStatistics() const
{
    resetWordsStatisticsCommand->resetWordsStatistics();
}

}
