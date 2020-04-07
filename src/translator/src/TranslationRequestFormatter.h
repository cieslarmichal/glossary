#pragma once

#include "boost/optional.hpp"

#include "Language.h"
#include "SourceText.h"
#include "webConnection/Request.h"

namespace glossary::translator
{
class TranslationRequestFormatter
{
public:
    virtual ~TranslationRequestFormatter() = default;

    virtual boost::optional<webConnection::Request> getFormattedRequest(const SourceText&, SourceLanguage,
                                                                        TargetLanguage) const = 0;
};
}
