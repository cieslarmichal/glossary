#include "translation/TranslationRequestFormatterImpl.h"

#include "StringHelper.h"

namespace translation
{

namespace
{
// TODO: get key from file and tell ppl to generate their own key from website
// TODO: https://translate.yandex.com/developers/keys

const std::string urlAddress{
    "https://translate.yandex.net/api/v1.5/tr.json/translate"};
const std::string apiKey{"trnsl.1.1.20200113T184314Z.f0829944dec57123."
                         "a22eb90262e3bd9a179a881dc6960e0a7f142c8d"};
const std::string stringToSplitBy{" "};
const std::string stringToJoinWith{"+"};
}

std::string TranslationRequestFormatterImpl::getFormattedRequest(
    const std::string& sourceText, SourceLanguage sourceLanguage,
    TargetLanguage targetLanguage) const
{
    if (sourceText.empty())
    {
        return {};
    }
    const auto formattedSourceText = getFormattedSourceText(sourceText);
    return getRequest(formattedSourceText, sourceLanguage, targetLanguage);
}

std::string TranslationRequestFormatterImpl::getFormattedSourceText(
    const std::string& sourceText) const
{
    const auto splitText =
        stringHelper::getSplitLines(sourceText, stringToSplitBy);
    return stringHelper::getJoinedLines(splitText, stringToJoinWith);
}

webConnection::Request TranslationRequestFormatterImpl::getRequest(
    const std::string& sourceText, translation::SourceLanguage sourceLanguage,
    translation::TargetLanguage targetLanguage) const
{
    const auto keyField = "key=" + apiKey;
    const auto text = "text=" + sourceText;
    const auto lang = "lang=" + toLanguageCode(sourceLanguage) + "-" +
                      toLanguageCode(targetLanguage);
    return webConnection::Request{urlAddress + "?" + keyField + "&" + text +
                                  "&" + lang};
}

}