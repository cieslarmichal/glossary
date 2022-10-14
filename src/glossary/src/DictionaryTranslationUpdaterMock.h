#pragma once

#include "gmock/gmock.h"

#include "DictionaryTranslationUpdater.h"

namespace glossary
{
class DictionaryTranslationUpdaterMock : public DictionaryTranslationUpdater
{
public:
    MOCK_METHOD3(updateDictionaryWordTranslation,
                 void(const dictionary::std::string&, const std::string& updatedTranslation,
                      const dictionary::std::string&));
    MOCK_METHOD2(updateDictionaryWordTranslation,
                 void(const dictionary::std::string&, const dictionary::std::string&));
    MOCK_METHOD1(updateDictionaryTranslations, void(const dictionary::std::string&));
};
}
