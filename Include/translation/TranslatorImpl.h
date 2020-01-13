#pragma once

#include "Translator.h"
#include "webConnection/HttpRequestHandler.h"
#include "TranslationDeserializer.h"
#include <memory>

namespace translation
{
class TranslatorImpl : public Translator
{
public:
    TranslatorImpl(std::shared_ptr<webConnection::HttpRequestHandler>, std::unique_ptr<TranslationDeserializer>);

    boost::optional<std::string> translate(const std::string&, SourceLanguage,
                          TargetLanguage) const override;

private:
    webConnection::Response getResponseFromTranslationApi(const webConnection::Request&) const;

    std::shared_ptr<webConnection::HttpRequestHandler> httpHandler;
    std::unique_ptr<TranslationDeserializer> translationDeserializer;
};
}