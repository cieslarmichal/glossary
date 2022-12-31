#pragma once

#include "dictionary/WordDescription.h"
#include "FormattedWordDescription.h"

namespace glossary::gui::view
{
class WordDescriptionFormatter
{
public:
    FormattedWordDescription formatWordDescription(const dictionary::WordDescription&) const;

private:
    QString formatEnglishWord(const std::string&) const;
    QList<QString> formatDefinitions(const std::vector<std::string>& definitions) const;
    QList<QString> formatExamples(const std::vector<std::string>& examples) const;
    QList<QString> formatSynonyms(const std::vector<std::string>& synonyms) const;
};
}
