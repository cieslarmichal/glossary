#pragma once

#include "gmock/gmock.h"

#include "DictionaryTranslationUpdater.h"

namespace glossary
{
class DictionaryTranslationUpdaterMock : public DictionaryTranslationUpdater
{
public:
    MOCK_METHOD3(updateDictionaryWordTranslation,
                 void(const dictionaryService::std::string&, const std::string& updatedTranslation,
                      const dictionaryService::DictionaryName&));
    MOCK_METHOD2(updateDictionaryWordTranslation,
                 void(const dictionaryService::std::string&, const dictionaryService::DictionaryName&));
    MOCK_METHOD1(updateDictionaryTranslations, void(const dictionaryService::DictionaryName&));
};
}
