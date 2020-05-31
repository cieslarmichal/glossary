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

    MOCK_CONST_METHOD0(getRandomPolishWord, boost::optional<std::string>());
    MOCK_CONST_METHOD1(getRandomPolishWord, boost::optional<std::string>(const DictionaryName&));
    MOCK_CONST_METHOD2(verifyPolishWordTranslation,
                       bool(const std::string& polishWord, const std::string& englishWord));
    MOCK_CONST_METHOD0(getDictionaries, Dictionaries());
    MOCK_CONST_METHOD0(getDictionariesNames, DictionaryNames());
    MOCK_CONST_METHOD1(getDictionaryWords, DictionaryWords(const DictionaryName&));
    MOCK_CONST_METHOD1(addDictionary, void(const DictionaryName&));
    MOCK_CONST_METHOD1(removeDictionary, void(const DictionaryName&));
    MOCK_CONST_METHOD2(addEnglishWordToDictionary, void(const EnglishWord&, const DictionaryName&));
    MOCK_CONST_METHOD3(addEnglishWordToDictionary,
                       void(const EnglishWord&, const std::string& translation, const DictionaryName&));
    MOCK_CONST_METHOD2(removeEnglishWordFromDictionary, void(const EnglishWord&, const DictionaryName&));
    MOCK_CONST_METHOD2(addDictionaryFromFile,
                       void(const DictionaryName&, const std::string& pathToFileWithDictionaryWords));
    MOCK_CONST_METHOD3(updateDictionaryWordTranslationManually,
                       void(const DictionaryName&, const EnglishWord&, const std::string& newTranslation));
    MOCK_CONST_METHOD2(updateDictionaryWordTranslationAutomatically,
                       void(const DictionaryName&, const EnglishWord&));
    MOCK_CONST_METHOD1(updateDictionaryTranslationsAutomatically, void(const DictionaryName&));
    MOCK_CONST_METHOD1(getEnglishWordDescription, WordDescription(const EnglishWord&));
    MOCK_CONST_METHOD0(getSupportedTranslatorLanguages, std::vector<std::string>());
    MOCK_CONST_METHOD3(translate, boost::optional<std::string>(const std::string& textToTranslate,
                                                               const std::string& sourceLanguage,
                                                               const std::string& targetLanguage));
    MOCK_CONST_METHOD1(getDictionaryStatistics, boost::optional<DictionaryStatistics>(const DictionaryName&));
    MOCK_CONST_METHOD0(getDictionariesStatistics, DictionariesStatistics());
    MOCK_CONST_METHOD0(resetStatistics, void());
};
}
