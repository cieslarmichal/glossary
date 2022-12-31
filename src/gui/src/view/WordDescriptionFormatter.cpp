#include "WordDescriptionFormatter.h"

namespace glossary::gui::view
{

FormattedWordDescription
WordDescriptionFormatter::formatWordDescription(const dictionary::WordDescription& wordDescription) const
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

QList<QString> WordDescriptionFormatter::formatDefinitions(const std::vector<std::string>& definitions) const
{
    QList<QString> formattedDefinitions;

    for (const auto& definition : definitions)
    {
        formattedDefinitions.push_back(QString::fromStdString(definition));
    }

    return formattedDefinitions;
}

QList<QString> WordDescriptionFormatter::formatExamples(const std::vector<std::string>& examples) const
{
    QList<QString> formattedExamples;

    for (const auto& example : examples)
    {
        formattedExamples.push_back(QString::fromStdString(example));
    }

    return formattedExamples;
}

QList<QString> WordDescriptionFormatter::formatSynonyms(const std::vector<std::string>& synonyms) const
{
    QList<QString> formattedSynonyms;

    for (const auto& synonym : synonyms)
    {
        formattedSynonyms.push_back(QString::fromStdString(synonym));
    }

    return formattedSynonyms;
}

}
