#pragma once

#include "Language.h"
#include "SourceText.h"
#include "webConnection/Request.h"

namespace glossary::translator
{
class TranslationRequestFormatter
{
public:
    virtual ~TranslationRequestFormatter() = default;

    virtual webConnection::Request getFormattedRequest(const SourceText&, SourceLanguage,
                                                       TargetLanguage) const = 0;
};
}
