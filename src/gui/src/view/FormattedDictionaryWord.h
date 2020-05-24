#pragma once

#include <QList>
#include <QString>

namespace glossary::gui::view
{
struct FormattedDictionaryWord
{
    QString englishWord;
    QString translation;
};

using FormattedDictionaryWords = QList<FormattedDictionaryWord>;

inline bool operator==(const FormattedDictionaryWord& lhs, const FormattedDictionaryWord& rhs)
{
    return lhs.englishWord == rhs.englishWord && lhs.translation == rhs.translation;
}
}
