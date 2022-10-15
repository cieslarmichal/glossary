#pragma once

#include "gmock/gmock.h"

#include "DictionaryTranslationUpdater.h"

namespace glossary
{
class DictionaryTranslationUpdaterMock : public DictionaryTranslationUpdater
{
public:
    MOCK_METHOD3(updateDictionaryWordTranslation,
                 void(const std::string&, const std::string& updatedTranslation,
                      const std::string&));
    MOCK_METHOD2(updateDictionaryWordTranslation,
                 void(const std::string&, const std::string&));
    MOCK_METHOD1(updateDictionaryTranslations, void(const std::string&));
};
}
