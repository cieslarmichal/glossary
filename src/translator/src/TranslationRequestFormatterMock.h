#pragma once

#include "gmock/gmock.h"

#include "TranslationRequestFormatter.h"

namespace translator
{

class TranslationRequestFormatterMock : public TranslationRequestFormatter
{
public:
    MOCK_CONST_METHOD3(getFormattedRequest,
                       webConnection::Request(const SourceText&, SourceLanguage, TargetLanguage));
};
}