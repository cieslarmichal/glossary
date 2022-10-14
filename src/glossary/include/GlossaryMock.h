#pragma once

#include "gmock/gmock.h"

#include "Glossary.h"

namespace glossary
{
class GlossaryMock : public Glossary
{
public:
    MOCK_CONST_METHOD0(checkConnectionToExternalServices, ExternalServicesStatus());
    MOCK_CONST_METHOD1(updateTranslateApiKeyLocation, void(const std::string& apiKeyLocation));
    MOCK_CONST_METHOD1(updateWordsApiKeyLocation, void(const std::string& apiKeyLocation));

    MOCK_CONST_METHOD0(getRandomPolishWord, std::optional<std::string>());
    MOCK_CONST_METHOD1(getRandomPolishWord, std::optional<std::string>(const std::string&));
    MOCK_CONST_METHOD2(verifyPolishWordTranslation,
                       bool(const std::string& polishWord, const std::string& englishWord));
    MOCK_CONST_METHOD0(getDictionaries, Dictionaries());
    MOCK_CONST_METHOD0(getDictionariesNames, std::vector<std::string>());
    MOCK_CONST_METHOD1(getDictionaryWords, std::vector<DictionaryWord>(const std::string&));
    MOCK_CONST_METHOD1(addDictionary, void(const std::string&));
    MOCK_CONST_METHOD1(removeDictionary, void(const std::string&));
    MOCK_CONST_METHOD2(addEnglishWordToDictionary, void(const std::string&, const std::string&));
    MOCK_CONST_METHOD3(addEnglishWordToDictionary,
                       void(const std::string&, const std::string& translation, const std::string&));
    MOCK_CONST_METHOD2(removeEnglishWordFromDictionary, void(const std::string&, const std::string&));
    MOCK_CONST_METHOD2(addDictionaryFromFile,
                       void(const std::string&, const std::string& pathToFileWithDictionaryWords));
    MOCK_CONST_METHOD3(updateDictionaryWordTranslationManually,
                       void(const std::string&, const std::string&, const std::string& newTranslation));
    MOCK_CONST_METHOD2(updateDictionaryWordTranslationAutomatically,
                       void(const std::string&, const std::string&));
    MOCK_CONST_METHOD1(updateDictionaryTranslationsAutomatically, void(const std::string&));
    MOCK_CONST_METHOD1(getEnglishWordDescription, WordDescription(const std::string&));
    MOCK_CONST_METHOD0(getSupportedTranslatorLanguages, std::vector<std::string>());
    MOCK_CONST_METHOD3(translate, std::optional<std::string>(const std::string& textToTranslate,
                                                               const std::string& sourceLanguage,
                                                               const std::string& targetLanguage));
    MOCK_CONST_METHOD1(getDictionaryStatistics, std::optional<DictionaryStatistics>(const std::string&));
    MOCK_CONST_METHOD0(getDictionariesStatistics, DictionariesStatistics());
    MOCK_CONST_METHOD0(resetStatistics, void());
};
}
