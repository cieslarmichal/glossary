#pragma once

#include "FormattedWordDescription.h"
#include "WordDescription.h"

namespace glossary::gui::view
{
class WordDescriptionFormatter
{
public:
    FormattedWordDescription formatWordDescription(const WordDescription&) const;

private:
    QString formatEnglishWord(const EnglishWord&) const;
    QList<QString> formatDefinitions(const Definitions&) const;
    QList<QString> formatSentences(const Sentences&) const;
};
}
