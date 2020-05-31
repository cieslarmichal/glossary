#pragma once

#include "gmock/gmock.h"

#include "TranslationService.h"

namespace glossary::translationService
{
class TranslationServiceMock : public TranslationService
{
public:
    MOCK_METHOD3(retrieveTranslation,
                 boost::optional<translator::TranslatedText>(const translator::SourceText&,
                                                             translator::SourceLanguage,
                                                             translator::TargetLanguage));
    MOCK_CONST_METHOD0(retrieveSupportedLanguages, std::vector<std::string>());
    MOCK_CONST_METHOD0(connectionToTranslateApiAvailable, TranslationApiStatus());
    MOCK_METHOD1(updateApiKeyLocation, void(const std::string& apiKeyLocation));
};
}