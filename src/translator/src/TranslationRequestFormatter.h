#pragma once

#include <boost/optional.hpp>

#include "Language.h"
#include "SourceText.h"

namespace glossary::translator
{
class TranslationRequestFormatter
{
public:
    virtual ~TranslationRequestFormatter() = default;

    virtual boost::optional<std::string> getFormattedRequest(const SourceText&, Language, Language,
                                                             const std::string& apiKey) const = 0;
};
}
