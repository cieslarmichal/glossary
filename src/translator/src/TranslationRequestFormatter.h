#pragma once

#include "Language.h"
#include "webConnection/Request.h"

namespace translator
{

class TranslationRequestFormatter
{
public:
    virtual ~TranslationRequestFormatter() = default;

    virtual webConnection::Request
    getFormattedRequest(const std::string&, SourceLanguage,
                        TargetLanguage) const = 0;
};
}
