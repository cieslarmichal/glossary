#pragma once

#include "gmock/gmock.h"

#include "TranslationService.h"

class TranslationServiceMock : public TranslationService
{
public:
    MOCK_METHOD3(translate,
                 boost::optional<translation::TranslatedText>(const std::string&, translation::SourceLanguage,
                                                              translation::TargetLanguage));
};
