#include "DictionaryWordAccumulator.h"

#include <sstream>

namespace glossary::gui::view
{
namespace
{
const QString dashSeparator{"-"};
}

QString
DictionaryWordAccumulator::accumulateDictionaryWord(const FormattedDictionaryWord& dictionaryWord) const
{
    if (dictionaryWord.englishWord.isEmpty())
    {
        return {};
    }

    QString accumulatedDictionaryWord = dictionaryWord.englishWord + " " + dashSeparator + " ";

    if (not dictionaryWord.translation.isEmpty())
    {
        accumulatedDictionaryWord += dictionaryWord.translation;
    }

    return accumulatedDictionaryWord;
}

std::optional<FormattedDictionaryWord>
DictionaryWordAccumulator::separateDictionaryWord(const QString& accumulatedDictionaryWord) const
{
    if (accumulatedDictionaryWord.isEmpty())
    {
        return std::nullopt;
    }

    std::stringstream dictionaryWordStream{accumulatedDictionaryWord.toStdString()};

    std::string englishWord, translation;

    char separator;

    dictionaryWordStream >> englishWord >> separator >> translation;

    if (englishWord.empty() || separator != dashSeparator)
    {
        return std::nullopt;
    }

    return FormattedDictionaryWord{QString::fromStdString(englishWord), QString::fromStdString(translation)};
}
}
