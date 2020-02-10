#pragma once

#include "SourceLanguage.h"
#include "TargetLanguage.h"
#include "webConnection/Request.h"

namespace translation
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
