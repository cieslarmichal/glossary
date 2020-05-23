#pragma once

#include <QList>
#include <QString>

namespace glossary::gui::view
{
struct FormattedWordDescription
{
    QString englishWord;
    QList<QString> definitions;
    QList<QString> examples;
    QList<QString> synonyms;
};

inline bool operator==(const FormattedWordDescription& lhs, const FormattedWordDescription& rhs)
{
    return lhs.englishWord == rhs.englishWord && lhs.definitions == rhs.definitions &&
           lhs.examples == rhs.examples && lhs.synonyms == rhs.synonyms;
}
}
