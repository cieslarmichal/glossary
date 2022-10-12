#include "DefaultTranslator.h"

#include <iostream>

#include "exceptions/InvalidApiKey.h"
#include "httpClient/HttpStatusCode.h"

namespace glossary::translator
{

DefaultTranslator::DefaultTranslator(std::shared_ptr<const httpClient::HttpClient> handler,
                                     std::unique_ptr<TranslationDeserializer> deserializer,
                                     std::unique_ptr<TranslationRequestFormatter> formatter)
    : httpHandler{std::move(handler)},
      translationDeserializer{std::move(deserializer)},
      requestFormatter{std::move(formatter)}
{
}

boost::optional<TranslatedText> DefaultTranslator::translate(const std::string& sourceText,
                                                             Language sourceLanguage, Language targetLanguage,
                                                             const std::string& apiKey) const
{
    const auto request =
        requestFormatter->getFormattedRequest(sourceText, sourceLanguage, targetLanguage, apiKey);

    if (request == boost::none)
    {
        return boost::none;
    }

    const auto response = tryGetResponseFromTranslationApi(*request);

    if (translationSucceeded(response.statusCode))
    {
        return translationDeserializer->deserialize(response.data);
    }
    else if (translationFailedDueToInvalidApiKey(response.statusCode))
    {
        throw exceptions::InvalidApiKey{"Invalid api key"};
    }

    std::cerr << "Error while translating text: " << sourceText;

    return boost::none;
}

httpClient::HttpResponse DefaultTranslator::tryGetResponseFromTranslationApi(const std::string& request) const
{
    return httpHandler->get({request});
}

bool DefaultTranslator::translationSucceeded(int statusCode) const
{
    return statusCode == httpClient::HttpStatusCode::Ok;
}

bool DefaultTranslator::translationFailedDueToInvalidApiKey(int responseCode) const
{
    return responseCode == httpClient::HttpStatusCode::BadRequest ||
           responseCode == httpClient::HttpStatusCode::Unauthorized;
}

}