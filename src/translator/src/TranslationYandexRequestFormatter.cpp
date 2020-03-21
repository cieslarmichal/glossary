#include "TranslationYandexRequestFormatter.h"

#include "utils/StringHelper.h"

namespace translator
{

namespace
{
// TODO: get key from file and tell ppl to generate their own key from website
// TODO: https://translate.yandex.com/developers/keys

const std::string urlAddress{"https://translate.yandex.net/api/v1.5/tr.json/translate"};
const std::string apiKey{"trnsl.1.1.20200113T184314Z.f0829944dec57123."
                         "a22eb90262e3bd9a179a881dc6960e0a7f142c8d"};
const std::string stringToSplitBy{" "};
const std::string stringToJoinWith{"+"};
}

std::string TranslationYandexRequestFormatter::getFormattedRequest(const std::string& sourceText,
                                                                 SourceLanguage sourceLanguage,
                                                                 TargetLanguage targetLanguage) const
{
    if (sourceText.empty())
    {
        return {};
    }
    const auto formattedSourceText = getFormattedSourceText(sourceText);
    return getRequest(formattedSourceText, sourceLanguage, targetLanguage);
}

std::string TranslationYandexRequestFormatter::getFormattedSourceText(const std::string& sourceText) const
{
    const auto splitText = utils::getSplitLines(sourceText, stringToSplitBy);
    return utils::getJoinedLines(splitText, stringToJoinWith);
}

webConnection::Request
TranslationYandexRequestFormatter::getRequest(const std::string& sourceText,
                                            translator::SourceLanguage sourceLanguage,
                                            translator::TargetLanguage targetLanguage) const
{
    const auto keyField = "key=" + apiKey;
    const auto text = "text=" + sourceText;
    const auto lang = "lang=" + toLanguageCode(sourceLanguage) + "-" + toLanguageCode(targetLanguage);
    return webConnection::Request{urlAddress + "?" + keyField + "&" + text + "&" + lang};
}

}