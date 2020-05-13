#include "DefaultTranslator.h"

#include <iostream>

#include "exceptions/InvalidApiKey.h"
#include "webConnection/exceptions/ConnectionFailed.h"

namespace glossary::translator
{
namespace
{
constexpr int successCode = 200;
constexpr int invalidApiKeyCode = 400;
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
                                                             translator::TargetLanguage targetLanguage,
                                                             const std::string& apiKey) const
{
    const auto request =
        requestFormatter->getFormattedRequest(sourceText, sourceLanguage, targetLanguage, apiKey);
    if (requestIsNotValid(request))
        return boost::none;

    const auto response = tryGetResponseFromTranslationApi(*request);
    {
        if (translationSucceeded(response.code))
        {
            return translationDeserializer->deserialize(response.content);
        }
        else if (translationFailedDueToInvalidApiKey(response.code))
        {
            throw exceptions::InvalidApiKey{"Invalid api key"};
        }
    }

    std::cerr << "Error while translating text: " << sourceText;
    return boost::none;
}

webConnection::Response
DefaultTranslator::tryGetResponseFromTranslationApi(const webConnection::Request& request) const
{
    return httpHandler->get(request);
    //    catch (const webConnection::exceptions::ConnectionFailed& e)
    //    {
    //        std::cerr << "Error while connecting to translation api: " << e.what();
    //        return boost::none;
    //    }
}

bool DefaultTranslator::requestIsNotValid(const boost::optional<webConnection::Request>& request) const
{
    return request == boost::none;
}

bool DefaultTranslator::translationSucceeded(webConnection::ResponseCode responseCode) const
{
    return responseCode == successCode;
}

bool DefaultTranslator::translationFailedDueToInvalidApiKey(webConnection::ResponseCode responseCode) const
{
    return responseCode == invalidApiKeyCode;
}

}