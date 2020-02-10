#pragma once

#include <memory>

#include "TranslationDeserializer.h"
#include "TranslationRequestFormatter.h"
#include "Translator.h"
#include "webConnection/HttpRequestHandler.h"

namespace translation
{
class TranslatorImpl : public Translator
{
public:
    TranslatorImpl(std::shared_ptr<webConnection::HttpRequestHandler>,
                   std::unique_ptr<TranslationDeserializer>,
                   std::unique_ptr<TranslationRequestFormatter>);

    boost::optional<std::string> translate(const std::string&, SourceLanguage,
                                           TargetLanguage) const override;

private:
    webConnection::Response
    getResponseFromTranslationApi(const webConnection::Request&) const;

    std::shared_ptr<webConnection::HttpRequestHandler> httpHandler;
    std::unique_ptr<TranslationDeserializer> translationDeserializer;
    std::unique_ptr<TranslationRequestFormatter> requestFormatter;
};
}