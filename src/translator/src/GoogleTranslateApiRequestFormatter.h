#pragma once

#include "TranslationRequestFormatter.h"

namespace glossary::translator
{
class GoogleTranslateApiRequestFormatter : public TranslationRequestFormatter
{
public:
    boost::optional<webConnection::Request> getFormattedRequest(const std::string&, SourceLanguage,
                                                                TargetLanguage) const override;

private:
    std::string getFormattedSourceText(const std::string&) const;
    webConnection::Request getRequest(const std::string&, translator::SourceLanguage,
                                      translator::TargetLanguage) const;
};
}