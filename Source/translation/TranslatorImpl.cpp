#include "translation/TranslatorImpl.h"

#include <iostream>

#include "webConnection/exceptions/ConnectionFailed.h"

namespace translation
{
namespace
{
constexpr int successCode = 200;
// TODO: class calling translationApi
}

TranslatorImpl::TranslatorImpl(
    std::shared_ptr<webConnection::HttpRequestHandler> handler,
    std::unique_ptr<TranslationDeserializer> deseralizer,
    std::unique_ptr<TranslationRequestFormatter> formatter)
    : httpHandler{std::move(handler)},
      translationDeserializer{std::move(deseralizer)}, requestFormatter{
                                                           std::move(formatter)}
{
}

boost::optional<TranslatedText>
TranslatorImpl::translate(const std::string& sourceText,
                          translation::SourceLanguage sourceLanguage,
                          translation::TargetLanguage targetLanguage) const
{
    const auto request = requestFormatter->getFormattedRequest(
        sourceText, sourceLanguage, targetLanguage);
    const auto response = getResponseFromTranslationApi(request);

    if (response.code == successCode)
    {
        return translationDeserializer->deserialize(response.content);
    }

    return boost::none;
}
webConnection::Response TranslatorImpl::getResponseFromTranslationApi(
    const webConnection::Request& request) const
{
    try
    {
        return httpHandler->get(request);
    }
    catch (const webConnection::exceptions::ConnectionFailed& e)
    {
        std::cerr << e.what();
    }
    return {};
}

}