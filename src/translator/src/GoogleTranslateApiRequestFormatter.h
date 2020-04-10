#pragma once

#include "TranslationRequestFormatter.h"

namespace glossary::translator
{
class GoogleTranslateApiRequestFormatter : public TranslationRequestFormatter
{
public:
    boost::optional<webConnection::Request> getFormattedRequest(const SourceText&, SourceLanguage,
                                                                TargetLanguage,
                                                                const std::string& apiKey) const override;

private:
    SourceText getFormattedSourceText(const SourceText&) const;
    webConnection::Request getRequest(const SourceText&, translator::SourceLanguage,
                                      translator::TargetLanguage, const std::string& apiKey) const;
};
}