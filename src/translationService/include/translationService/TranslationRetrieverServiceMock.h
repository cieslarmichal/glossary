#pragma once

#include "gmock/gmock.h"

#include "TranslationRetrieverService.h"

namespace glossary::translationService
{
class TranslationRetrieverServiceMock : public TranslationRetrieverService
{
public:
    MOCK_METHOD3(retrieveTranslation,
                 boost::optional<translator::TranslatedText>(const translator::SourceText&,
                                                             translator::SourceLanguage,
                                                             translator::TargetLanguage));
    MOCK_CONST_METHOD0(retrieveSupportedLanguages, std::vector<std::string>());
    MOCK_METHOD0(connectionToTranslateApiAvailable, TranslationApiStatus());
};
}