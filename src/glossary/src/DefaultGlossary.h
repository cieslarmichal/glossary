#pragma once

#include <memory>

#include "dictionary/commands/AddWordToDictionaryCommand.h"
#include "dictionary/commands/CreateDictionaryCommand.h"
#include "dictionary/commands/CreateDictionaryFromCsvFileCommand.h"
#include "dictionary/commands/RemoveDictionaryCommand.h"
#include "dictionary/commands/RemoveWordFromDictionaryCommand.h"
#include "dictionary/commands/UpdateWordTranslationInDictionaryCommand.h"
#include "dictionary/queries/GetDictionariesEnglishWordsQuery.h"
#include "dictionary/queries/GetDictionariesNamesQuery.h"
#include "dictionary/queries/GetDictionariesQuery.h"
#include "dictionary/queries/GetDictionaryEnglishWordsQuery.h"
#include "dictionary/queries/GetDictionaryQuery.h"
#include "dictionary/queries/GetRandomWordFromDictionariesQuery.h"
#include "dictionary/queries/GetRandomWordFromDictionaryQuery.h"
#include "dictionary/queries/GetWordDescriptionQuery.h"
#include "DictionaryStatisticsCounter.h"
#include "Glossary.h"
#include "statistics/commands/AddCorrectAnswerCommand.h"
#include "statistics/commands/AddIncorrectAnswerCommand.h"
#include "statistics/commands/AddWordStatisticsCommand.h"
#include "statistics/commands/ResetWordsStatisticsCommand.h"
#include "statistics/queries/GetWordsStatisticsQuery.h"
#include "translation/queries/GetSupportedLanguagesQuery.h"
#include "translation/queries/GetTranslationQuery.h"

namespace glossary
{
class DefaultGlossary : public Glossary
{
public:
    DefaultGlossary(
        std::unique_ptr<DictionaryStatisticsCounter>, std::unique_ptr<dictionary::AddWordToDictionaryCommand>,
        std::unique_ptr<dictionary::CreateDictionaryCommand>, std::unique_ptr<dictionary::RemoveDictionaryCommand>,
        std::unique_ptr<dictionary::CreateDictionaryFromCsvFileCommand>,
        std::unique_ptr<dictionary::RemoveWordFromDictionaryCommand>,
        std::unique_ptr<dictionary::UpdateWordTranslationInDictionaryCommand>,
        std::unique_ptr<dictionary::GetDictionariesEnglishWordsQuery>,
        std::unique_ptr<dictionary::GetDictionariesNamesQuery>, std::unique_ptr<dictionary::GetDictionariesQuery>,
        std::unique_ptr<dictionary::GetDictionaryEnglishWordsQuery>, std::unique_ptr<dictionary::GetDictionaryQuery>,
        std::unique_ptr<dictionary::GetRandomWordFromDictionariesQuery>,
        std::unique_ptr<dictionary::GetRandomWordFromDictionaryQuery>,
        std::shared_ptr<dictionary::GetWordDescriptionQuery>, std::unique_ptr<statistics::AddCorrectAnswerCommand>,
        std::unique_ptr<statistics::AddIncorrectAnswerCommand>, std::unique_ptr<statistics::AddWordStatisticsCommand>,
        std::unique_ptr<statistics::ResetWordsStatisticsCommand>, std::unique_ptr<statistics::GetWordsStatisticsQuery>,
        std::shared_ptr<translation::GetTranslationQuery>, std::unique_ptr<translation::GetSupportedLanguagesQuery>);

    std::optional<std::string> getRandomPolishWord() const override;
    std::optional<std::string> getRandomPolishWord(const std::string&) const override;
    bool verifyPolishWordTranslation(const std::string& polishWord, const std::string& englishWord) const override;
    std::vector<dictionary::Dictionary> getDictionaries() const override;
    std::vector<std::string> getDictionariesNames() const override;
    std::vector<dictionary::DictionaryWord> getDictionaryWords(const std::string&) const override;
    void addDictionary(const std::string&) const override;
    void removeDictionary(const std::string&) const override;
    void addEnglishWordToDictionary(const std::string&, const std::string&) const override;
    void addEnglishWordToDictionary(const std::string&, const std::string& translation,
                                    const std::string&) const override;
    void removeEnglishWordFromDictionary(const std::string&, const std::string&) const override;
    void addDictionaryFromFile(const std::string&, const std::string& pathToFileWithDictionaryWords) const override;
    void updateDictionaryWordTranslationManually(const std::string&, const std::string&,
                                                 const std::string& newTranslation) const override;
    void updateDictionaryWordTranslationAutomatically(const std::string&, const std::string&) const override;
    void updateDictionaryTranslationsAutomatically(const std::string&) const override;
    dictionary::WordDescription getEnglishWordDescription(const std::string&) const override;
    std::optional<std::string> translate(const std::string& textToTranslate, const std::string& sourceLanguage,
                                         const std::string& targetLanguage) const override;
    std::vector<std::string> getSupportedTranslatorLanguages() const override;
    std::optional<DictionaryStatistics> getDictionaryStatistics(const std::string&) const override;
    DictionariesStatistics getDictionariesStatistics() const override;
    void resetStatistics() const override;

private:
    void synchronizeEnglishWords();

    std::unique_ptr<DictionaryStatisticsCounter> dictionaryStatisticsCounter;
    std::unique_ptr<dictionary::AddWordToDictionaryCommand> addWordToDictionaryCommand;
    std::unique_ptr<dictionary::CreateDictionaryCommand> createDictionaryCommand;
    std::unique_ptr<dictionary::RemoveDictionaryCommand> removeDictionaryCommand;
    std::unique_ptr<dictionary::CreateDictionaryFromCsvFileCommand> createDictionaryFromCsvFileCommand;
    std::unique_ptr<dictionary::RemoveWordFromDictionaryCommand> removeWordFromDictionaryCommand;
    std::unique_ptr<dictionary::UpdateWordTranslationInDictionaryCommand> updateWordTranslationInDictionaryCommand;
    std::unique_ptr<dictionary::GetDictionariesEnglishWordsQuery> getDictionariesEnglishWordsQuery;
    std::unique_ptr<dictionary::GetDictionariesNamesQuery> getDictionariesNamesQuery;
    std::unique_ptr<dictionary::GetDictionariesQuery> getDictionariesQuery;
    std::unique_ptr<dictionary::GetDictionaryEnglishWordsQuery> getDictionaryEnglishWordsQuery;
    std::unique_ptr<dictionary::GetDictionaryQuery> getDictionaryQuery;
    std::unique_ptr<dictionary::GetRandomWordFromDictionariesQuery> getRandomWordFromDictionariesQuery;
    std::unique_ptr<dictionary::GetRandomWordFromDictionaryQuery> getRandomWordFromDictionaryQuery;
    std::shared_ptr<dictionary::GetWordDescriptionQuery> getWordDescriptionQuery;
    std::unique_ptr<statistics::AddCorrectAnswerCommand> addCorrectAnswerCommand;
    std::unique_ptr<statistics::AddIncorrectAnswerCommand> addIncorrectAnswerCommand;
    std::unique_ptr<statistics::AddWordStatisticsCommand> addWordStatisticsCommand;
    std::unique_ptr<statistics::ResetWordsStatisticsCommand> resetWordsStatisticsCommand;
    std::unique_ptr<statistics::GetWordsStatisticsQuery> getWordsStatisticsQuery;
    std::shared_ptr<translation::GetTranslationQuery> getTranslationQuery;
    std::unique_ptr<translation::GetSupportedLanguagesQuery> getSupportedLanguagesQuery;
};
}
