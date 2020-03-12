#include "TranslatorImpl.h"

#include <iostream>

#include "webConnection/exceptions/ConnectionFailed.h"

namespace translator
{
namespace
{
constexpr int successCode = 200;
}

TranslatorImpl::TranslatorImpl(std::shared_ptr<webConnection::HttpHandler> handler,
                               std::unique_ptr<TranslationDeserializer> deserializer,
                               std::unique_ptr<TranslationRequestFormatter> formatter)
    : httpHandler{std::move(handler)},
      translationDeserializer{std::move(deserializer)},
      requestFormatter{std::move(formatter)}
{
}

boost::optional<TranslatedText> TranslatorImpl::translate(const std::string& sourceText,
                                                          translator::SourceLanguage sourceLanguage,
                                                          translator::TargetLanguage targetLanguage) const
{
    const auto request = requestFormatter->getFormattedRequest(sourceText, sourceLanguage, targetLanguage);
    const auto response = getResponseFromTranslationApi(request);

    if (response.code == successCode)
    {
        return translationDeserializer->deserialize(response.content);
    }

    return boost::none;
}
webConnection::Response
TranslatorImpl::getResponseFromTranslationApi(const webConnection::Request& request) const
{
    try
    {
        return httpHandler->get(request);
    }
    catch (const webConnection::exceptions::ConnectionFailed& e)
    {
        std::cerr << "Error while connecting to translation api: " << e.what();
    }
    return {};
}

}