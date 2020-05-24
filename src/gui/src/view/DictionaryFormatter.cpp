#include "DictionaryFormatter.h"

namespace glossary::gui::view
{

FormattedDictionaries DictionaryFormatter::getFormattedDictionaries(const Dictionaries & dictionaries) const
{
    FormattedDictionaries formattedDictionaries;
    for (const auto& dictionary : dictionaries)
    {
        formattedDictionaries.push_back(getFormattedDictionary(dictionary));
    }
    return formattedDictionaries;
}

FormattedDictionary DictionaryFormatter::getFormattedDictionary(const Dictionary& dictionary) const
{
    auto dictionaryName = getFormattedDictionaryName(dictionary.name);
    auto formattedDictionaryWords = getFormattedDictionaryWords(dictionary.words);
    return {dictionaryName, formattedDictionaryWords};
}

QString DictionaryFormatter::getFormattedDictionaryName(const DictionaryName& dictionaryName) const
{
    return QString::fromStdString(dictionaryName);
}

FormattedDictionaryWords DictionaryFormatter::getFormattedDictionaryWords(const DictionaryWords& dictionaryWords) const
{
    FormattedDictionaryWords formattedDictionaryWords;
    for (const auto& dictionaryWord : dictionaryWords)
    {
        QString englishWord = QString::fromStdString(dictionaryWord.englishWord);
        QString translation = dictionaryWord.translation? QString::fromStdString(*dictionaryWord.translation) : "";
        formattedDictionaryWords.push_back({englishWord, translation});
    }
    return formattedDictionaryWords;
}

}

