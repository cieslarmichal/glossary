#include "DictionaryFormatter.h"

namespace glossary::gui::view
{

FormattedDictionaries
DictionaryFormatter::getFormattedDictionaries(const std::vector<dictionary::Dictionary>& dictionaries) const
{
    FormattedDictionaries formattedDictionaries;

    for (const auto& dictionary : dictionaries)
    {
        formattedDictionaries.push_back(getFormattedDictionary(dictionary));
    }

    return formattedDictionaries;
}

FormattedDictionary DictionaryFormatter::getFormattedDictionary(const dictionary::Dictionary& dictionary) const
{
    auto dictionaryName = getFormattedDictionaryName(dictionary.name);

    auto formattedDictionaryWords = getFormattedDictionaryWords(dictionary.words);

    return {dictionaryName, formattedDictionaryWords};
}

QString DictionaryFormatter::getFormattedDictionaryName(const std::string& dictionaryName) const
{
    return QString::fromStdString(dictionaryName);
}

FormattedDictionaryWords
DictionaryFormatter::getFormattedDictionaryWords(const std::vector<dictionary::DictionaryWord>& dictionaryWords) const
{
    FormattedDictionaryWords formattedDictionaryWords;

    for (const auto& dictionaryWord : dictionaryWords)
    {
        QString englishWord = QString::fromStdString(dictionaryWord.englishWord);

        QString translation =
            dictionaryWord.translation ? QString::fromStdString(*dictionaryWord.translation) : "";

        formattedDictionaryWords.push_back({englishWord, translation});
    }

    return formattedDictionaryWords;
}

}
