#include "TranslationsMemoryStorage.h"

namespace glossary::translation
{
static auto& getTranslationByPosition(const std::vector<Translation>& translations,
                                      std::vector<Translation>::const_iterator position)
{
    const auto distance = std::vector<Translation>::size_type(std::distance(translations.cbegin(), position));

    return translations.at(distance);
}

void TranslationsMemoryStorage::addTranslation(Translation translation)
{
    if (not contains(translation.sourceText))
    {
        translations.emplace_back(std::move(translation));
    }
}

std::optional<Translation> TranslationsMemoryStorage::getTranslation(const std::string& polishWord) const
{
    auto translationPosition = findTranslationPosition(polishWord);

    if (translationPosition != translations.end())
    {
        return getTranslationByPosition(translations, translationPosition);
    }

    return std::nullopt;
}

std::vector<Translation> TranslationsMemoryStorage::getTranslations() const
{
    return translations;
}

bool TranslationsMemoryStorage::contains(const std::string& polishWord) const
{
    return findTranslationPosition(polishWord) != translations.end();
}

std::vector<Translation>::size_type TranslationsMemoryStorage::size() const
{
    return translations.size();
}

bool TranslationsMemoryStorage::empty() const
{
    return translations.empty();
}

std::vector<Translation>::const_iterator
TranslationsMemoryStorage::findTranslationPosition(const std::string& wordToFind) const
{
    return std::find_if(translations.begin(), translations.end(),
                        [wordToFind](const Translation& translation)
                        { return translation.sourceText == wordToFind; });
}

}