#include "DefaultTranslator.h"

#include <iostream>

#include "webConnection/exceptions/ConnectionFailed.h"

namespace glossary::translator
{
namespace
{
constexpr int successCode = 200;
}

DefaultTranslator::DefaultTranslator(std::shared_ptr<const webConnection::HttpHandler> handler,
                                     std::unique_ptr<TranslationDeserializer> deserializer,
                                     std::unique_ptr<TranslationRequestFormatter> formatter)
    : httpHandler{std::move(handler)},
      translationDeserializer{std::move(deserializer)},
      requestFormatter{std::move(formatter)}
{
}

boost::optional<TranslatedText> DefaultTranslator::translate(const std::string& sourceText,
                                                             translator::SourceLanguage sourceLanguage,
                                                             translator::TargetLanguage targetLanguage) const
{
    const auto request = requestFormatter->getFormattedRequest(sourceText, sourceLanguage, targetLanguage);
    if (requestIsNotValid(request))
        return boost::none;

    if (const auto response = getResponseFromTranslationApi(*request))
    {
        if (translationSucceeded(response->code))
            return translationDeserializer->deserialize(response->content);
    }

    std::cerr << "Error while translating text: " << sourceText;
    return boost::none;
}

boost::optional<webConnection::Response>
DefaultTranslator::getResponseFromTranslationApi(const webConnection::Request& request) const
{
    try
    {
        return httpHandler->get(request);
    }
    catch (const webConnection::exceptions::ConnectionFailed& e)
    {
        std::cerr << "Error while connecting to translation api: " << e.what();
        return boost::none;
    }
}

bool DefaultTranslator::requestIsNotValid(const boost::optional<webConnection::Request>& request) const
{
    return request == boost::none;
}

bool DefaultTranslator::translationSucceeded(webConnection::ResponseCode responseCode) const
{
    return responseCode == successCode;
}

}