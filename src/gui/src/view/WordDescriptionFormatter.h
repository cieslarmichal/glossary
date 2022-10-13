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
    QString formatEnglishWord(const std::string&) const;
    QList<QString> formatDefinitions(const Definitions&) const;
    QList<QString> formatExamples(const Examples&) const;
    QList<QString> formatSynonyms(const Synonyms&) const;
};
}
