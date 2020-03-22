#include "TranslationsMemoryStorage.h"

namespace translationRepository
{

static auto& getWordStatisticsByPosition(const Translations& translations,
                                         Translations::const_iterator position)
{
    const auto distance = Translations::size_type(std::distance(translations.cbegin(), position));
    return translations.at(distance);
}

void TranslationsMemoryStorage::addTranslation(Translation translation)
{
    if (not contains(translation.sourceText))
    {
        translations.emplace_back(std::move(translation));
    }
}

boost::optional<Translation> TranslationsMemoryStorage::getTranslation(const SourceText& polishWord) const
{
    auto translationPosition = findTranslationPosition(polishWord);
    if (translationPosition != translations.end())
    {
        return getWordStatisticsByPosition(translations, translationPosition);
    }
    return boost::none;
}

Translations TranslationsMemoryStorage::getTranslations() const
{
    return translations;
}

bool TranslationsMemoryStorage::contains(const SourceText& polishWord) const
{
    return findTranslationPosition(polishWord) != translations.end();
}

Translations::size_type TranslationsMemoryStorage::size() const
{
    return translations.size();
}

bool TranslationsMemoryStorage::empty() const
{
    return translations.empty();
}

Translations::const_iterator
TranslationsMemoryStorage::findTranslationPosition(const SourceText& wordToFind) const
{
    return std::find_if(
        translations.begin(), translations.end(),
        [wordToFind](const Translation& translation) { return translation.sourceText == wordToFind; });
}

}