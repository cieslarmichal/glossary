#include "GoogleTranslateApiRequestFormatter.h"

#include "utils/StringHelper.h"

namespace glossary::translator
{
namespace
{
const std::string urlAddress{"https://translation.googleapis.com/language/translate/v2?"};
const std::string stringToSplitBy{" "};
const std::string stringToJoinWith{"+"};
}

boost::optional<std::string>
GoogleTranslateApiRequestFormatter::getFormattedRequest(const SourceText& sourceText, Language sourceLanguage,
                                                        Language targetLanguage,
                                                        const std::string& apiKey) const
{
    if (sourceText.empty())
        return boost::none;

    const auto formattedSourceText = getFormattedSourceText(sourceText);
    return getRequest(formattedSourceText, sourceLanguage, targetLanguage, apiKey);
}

SourceText GoogleTranslateApiRequestFormatter::getFormattedSourceText(const SourceText& sourceText) const
{
    const auto splitText = utils::split(sourceText, stringToSplitBy);
    return utils::join(splitText, stringToJoinWith);
}

std::string GoogleTranslateApiRequestFormatter::getRequest(const SourceText& sourceText,
                                                           Language sourceLanguage, Language targetLanguage,
                                                           const std::string& apiKey) const
{
    const auto keyField = "key=" + apiKey;

    const auto text = "q=" + sourceText;

    const auto source = "source=" + toLanguageCode(sourceLanguage);

    const auto target = "target=" + toLanguageCode(targetLanguage);

    return std::string{urlAddress + keyField + "&" + text + "&" + source + "&" + target};
}

}