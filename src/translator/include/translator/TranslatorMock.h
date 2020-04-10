#pragma once

#include "gmock/gmock.h"

#include "Translator.h"

namespace glossary::translator
{

class TranslatorMock : public Translator
{
public:
    MOCK_CONST_METHOD4(translate, boost::optional<TranslatedText>(const SourceText&, SourceLanguage,
                                                                  TargetLanguage, const std::string& apiKey));
};
}