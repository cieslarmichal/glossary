#pragma once

#include "gmock/gmock.h"

#include "translation/Translator.h"

namespace translation
{
// TODO:: use newer gmock version

class TranslatorMock : public Translator
{
public:
    MOCK_CONST_METHOD3(translate, boost::optional<std::string>(const std::string&, SourceLanguage,
        TargetLanguage));
};
}