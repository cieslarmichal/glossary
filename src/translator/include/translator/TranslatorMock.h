#pragma once

#include "gmock/gmock.h"

#include "Translator.h"

namespace translator
{

class TranslatorMock : public Translator
{
public:
    MOCK_CONST_METHOD3(translate,
                       boost::optional<std::string>(const std::string&, SourceLanguage, TargetLanguage));
};
}