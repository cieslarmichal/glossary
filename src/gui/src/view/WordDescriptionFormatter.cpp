#include "WordDescriptionFormatter.h"

namespace glossary::gui::view
{

FormattedWordDescription
WordDescriptionFormatter::formatWordDescription(const WordDescription& wordDescription) const
{
    auto englishWord = formatEnglishWord(wordDescription.englishWord);
    auto definitions = formatDefinitions(wordDescription.description.definitionsWithExamples);
    auto sentences = formatSentences(wordDescription.description.sentences);
    return {englishWord, definitions, sentences};
}

QString WordDescriptionFormatter::formatEnglishWord(const EnglishWord& englishWord) const
{
    return QString::fromStdString(englishWord);
}

QList<QString> WordDescriptionFormatter::formatDefinitions(const Definitions& definitionsAndExamples) const
{
    QList<QString> formattedDefinitions;
    for (const auto& definitionAndExample : definitionsAndExamples)
    {
        QString definition = QString::fromStdString(definitionAndExample.definition);
        formattedDefinitions.push_back(definition);
        if (definitionAndExample.example)
        {
            QString example = "// " + QString::fromStdString(*definitionAndExample.example);
            formattedDefinitions.push_back(example);
        }
        else
        {
            formattedDefinitions.push_back("");
        }
    }
    return formattedDefinitions;
}

QList<QString> WordDescriptionFormatter::formatSentences(const Sentences& sentences) const
{
    QList<QString> formattedSentences;
    for (const auto& sentence : sentences)
    {
        formattedSentences.push_back(QString::fromStdString(sentence));
    }
    return formattedSentences;
}

}
