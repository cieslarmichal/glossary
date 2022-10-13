#include "WordDescriptionFormatter.h"

namespace glossary::gui::view
{

FormattedWordDescription
WordDescriptionFormatter::formatWordDescription(const WordDescription& wordDescription) const
{
    auto englishWord = formatEnglishWord(wordDescription.englishWord);
    auto definitions = formatDefinitions(wordDescription.definitions);
    auto examples = formatExamples(wordDescription.examples);
    auto synonyms = formatSynonyms(wordDescription.synonyms);
    return {englishWord, definitions, examples, synonyms};
}

QString WordDescriptionFormatter::formatEnglishWord(const std::string& englishWord) const
{
    return QString::fromStdString(englishWord);
}

QList<QString> WordDescriptionFormatter::formatDefinitions(const Definitions& definitions) const
{
    QList<QString> formattedDefinitions;
    for (const auto& definition : definitions)
    {
        formattedDefinitions.push_back(QString::fromStdString(definition));
    }
    return formattedDefinitions;
}

QList<QString> WordDescriptionFormatter::formatExamples(const Examples& examples) const
{
    QList<QString> formattedExamples;
    for (const auto& example : examples)
    {
        formattedExamples.push_back(QString::fromStdString(example));
    }
    return formattedExamples;
}

QList<QString> WordDescriptionFormatter::formatSynonyms(const Synonyms& synonyms) const
{
    QList<QString> formattedSynonyms;
    for (const auto& synonym : synonyms)
    {
        formattedSynonyms.push_back(QString::fromStdString(synonym));
    }
    return formattedSynonyms;
}

}
