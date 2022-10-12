#pragma once

#include "TranslationRequestFormatter.h"

namespace glossary::translator
{
class GoogleTranslateApiRequestFormatter : public TranslationRequestFormatter
{
public:
    boost::optional<std::string> getFormattedRequest(const SourceText&, Language, Language,
                                                     const std::string& apiKey) const override;

private:
    SourceText getFormattedSourceText(const SourceText&) const;
    std::string getRequest(const SourceText&, Language, Language, const std::string& apiKey) const;
};
}