#include "FormattedDictionariesStorage.h"

#include <algorithm>

namespace glossary::gui::view
{
FormattedDictionariesStorage::FormattedDictionariesStorage(QList<FormattedDictionary> dictionariesInit)
    : dictionaries{std::move(dictionariesInit)}
{
}

void FormattedDictionariesStorage::updateDictionaryWords(const QString& dictionaryName,
                                                         const FormattedDictionaryWords& words)
{
    auto foundDictionary =
        std::find_if(dictionaries.begin(), dictionaries.end(),
                     [&](const FormattedDictionary& dict) { return dict.dictionaryName == dictionaryName; });
    if (foundDictionary != dictionaries.end())
    {
        foundDictionary->dictionaryWords = words;
    }
}

void FormattedDictionariesStorage::updateDictionaries(const QList<FormattedDictionary>& updatedDictionaries)
{
    if (dictionaries != updatedDictionaries)
    {
        dictionaries = updatedDictionaries;
    }
}

QList<FormattedDictionary> FormattedDictionariesStorage::getDictionaries() const
{
    return dictionaries;
}

QStringList FormattedDictionariesStorage::getDictionaryNames() const
{
    QStringList dictionaryNames;
    for (const auto& dictionary : dictionaries)
    {
        dictionaryNames.push_back(dictionary.dictionaryName);
    }
    return dictionaryNames;
}

FormattedDictionaryWords FormattedDictionariesStorage::getDictionaryWords(const QString& dictionaryName) const
{
    auto foundDictionary =
        std::find_if(dictionaries.begin(), dictionaries.end(),
                     [&](const FormattedDictionary& dict) { return dict.dictionaryName == dictionaryName; });
    if (foundDictionary != dictionaries.end())
    {
        return foundDictionary->dictionaryWords;
    }
    return {};
}

bool FormattedDictionariesStorage::dictionariesAreEmpty() const
{
    return dictionaries.empty();
}

}
