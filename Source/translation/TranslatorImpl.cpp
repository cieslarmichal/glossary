#include "translation/TranslatorImpl.h"

#include <iostream>

#include "exceptions/ConnectionFailed.h"

namespace translation
{
namespace
{
// TODO: get key from file and tell ppl to generate their own key from website
// TODO: https://translate.yandex.com/developers/keys

// TODO: class calling translationApi

const std::string urlAddress{
    "https://translate.yandex.net/api/v1.5/tr.json/translate"};
const std::string apiKey{"trnsl.1.1.20200113T184314Z.f0829944dec57123."
                         "a22eb90262e3bd9a179a881dc6960e0a7f142c8d"};
const int successCode = 200;
webConnection::Request getRequest(const std::string&,
                                  translation::SourceLanguage,
                                  translation::TargetLanguage);
}

TranslatorImpl::TranslatorImpl(
    std::shared_ptr<webConnection::HttpRequestHandler> handler,
    std::unique_ptr<TranslationDeserializer> deseralizer)
    : httpHandler{std::move(handler)}, translationDeserializer{
                                           std::move(deseralizer)}
{
}

boost::optional<std::string>
TranslatorImpl::translate(const std::string& sourceText,
                          translation::SourceLanguage sourceLanguage,
                          translation::TargetLanguage targetLanguage) const
{
    const auto request = getRequest(sourceText, sourceLanguage, targetLanguage);
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
    catch (const exceptions::ConnectionFailed& e)
    {
        std::cerr << e.what();
    }
    return {};
}

namespace
{
webConnection::Request getRequest(const std::string& sourceText,
                                  translation::SourceLanguage sourceLanguage,
                                  translation::TargetLanguage targetLanguage)
{
    const auto keyField = "key=" + apiKey;
    const auto text = "text=" + sourceText;
    const auto lang = "lang=" + toLanguageCode(sourceLanguage) + "-" +
                      toLanguageCode(targetLanguage);
    return urlAddress + "?" + keyField + "&" + text + "&" + lang;
}

}

}