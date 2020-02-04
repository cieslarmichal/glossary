#pragma once

#include "gmock/gmock.h"

#include "translation/Translator.h"

namespace translation
{

class TranslatorMock : public Translator
{
public:
    MOCK_CONST_METHOD3(translate,
                       boost::optional<std::string>(const std::string&,
                                                    SourceLanguage,
                                                    TargetLanguage));
};
}