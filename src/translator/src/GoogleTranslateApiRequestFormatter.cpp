#include "GoogleTranslateApiRequestFormatter.h"

#include "utils/StringHelper.h"

namespace glossary::translator
{
namespace
{
// TODO: reading key from file
const std::string urlAddress{"https://translation.googleapis.com/language/translate/v2?"};
const std::string apiKey{"AIzaSyCzXw_W97vKC5sSHXpNSCSpB5STCZkk08o"};
const std::string stringToSplitBy{" "};
const std::string stringToJoinWith{"+"};
}

boost::optional<webConnection::Request> GoogleTranslateApiRequestFormatter::getFormattedRequest(
    const std::string& sourceText, SourceLanguage sourceLanguage, TargetLanguage targetLanguage) const
{
    if (sourceText.empty())
        return boost::none;

    const auto formattedSourceText = getFormattedSourceText(sourceText);
    return getRequest(formattedSourceText, sourceLanguage, targetLanguage);
}

std::string GoogleTranslateApiRequestFormatter::getFormattedSourceText(const std::string& sourceText) const
{
    const auto splitText = utils::split(sourceText, stringToSplitBy);
    return utils::join(splitText, stringToJoinWith);
}

webConnection::Request
GoogleTranslateApiRequestFormatter::getRequest(const std::string& sourceText, SourceLanguage sourceLanguage,
                                               translator::TargetLanguage targetLanguage) const
{
    const auto keyField = "key=" + apiKey;
    const auto text = "q=" + sourceText;
    const auto source = "source=" + toLanguageCode(sourceLanguage);
    const auto target = "target=" + toLanguageCode(targetLanguage);
    return webConnection::Request{urlAddress + keyField + "&" + text + "&" + source + "&" + target};
}

}