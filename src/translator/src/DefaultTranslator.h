#pragma once

#include <memory>

#include "TranslationDeserializer.h"
#include "TranslationRequestFormatter.h"
#include "Translator.h"
#include "webConnection/HttpHandler.h"

namespace glossary::translator
{
class DefaultTranslator : public Translator
{
public:
    DefaultTranslator(std::shared_ptr<const webConnection::HttpHandler>,
                      std::unique_ptr<TranslationDeserializer>, std::unique_ptr<TranslationRequestFormatter>);

    boost::optional<TranslatedText> translate(const std::string&, SourceLanguage,
                                              TargetLanguage) const override;

private:
    boost::optional<webConnection::Response>
    getResponseFromTranslationApi(const webConnection::Request&) const;
    bool requestIsNotValid(const boost::optional<webConnection::Request>&) const;
    bool translationSucceeded(webConnection::ResponseCode) const;

    std::shared_ptr<const webConnection::HttpHandler> httpHandler;
    std::unique_ptr<TranslationDeserializer> translationDeserializer;
    std::unique_ptr<TranslationRequestFormatter> requestFormatter;
};
}