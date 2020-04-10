#pragma once

#include "gmock/gmock.h"

#include "TranslationRequestFormatter.h"

namespace glossary::translator
{
class TranslationRequestFormatterMock : public TranslationRequestFormatter
{
public:
    MOCK_CONST_METHOD4(getFormattedRequest,
                       boost::optional<webConnection::Request>(const SourceText&, SourceLanguage,
                                                               TargetLanguage, const std::string& apiKey));
};
}