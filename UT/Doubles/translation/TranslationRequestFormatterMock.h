#pragma once

#include "gmock/gmock.h"

#include "translation/TranslationRequestFormatter.h"

namespace translation
{

class TranslationRequestFormatterMock : public TranslationRequestFormatter
{
public:
    MOCK_CONST_METHOD3(getFormattedRequest,
                       webConnection::Request(const std::string&,
                           SourceLanguage,
                           TargetLanguage));
};
}