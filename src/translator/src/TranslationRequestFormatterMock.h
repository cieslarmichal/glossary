#pragma once

#include "gmock/gmock.h"

#include "TranslationRequestFormatter.h"

namespace glossary::translator
{
class TranslationRequestFormatterMock : public TranslationRequestFormatter
{
public:
    MOCK_CONST_METHOD4(getFormattedRequest,
                       boost::optional<std::string>(const SourceText&, Language, Language,
                                                    const std::string& apiKey));
};
}