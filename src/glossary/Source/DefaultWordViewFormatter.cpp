#include "DefaultWordViewFormatter.h"

#include <sstream>

namespace glossary
{
size_t DefaultWordViewFormatter::amountOfDefinitionsToView{5};
size_t DefaultWordViewFormatter::amountOfSentencesToView{2};

std::string DefaultWordViewFormatter::formatSingleWordView(const std::string& word) const
{
    return "Word: " + word + "\n";
}

std::string DefaultWordViewFormatter::formatWordDescriptionView(
    const wordDescriptionRepository::WordDescription& wordDescription) const
{
    std::stringstream wordView;
    wordView << "English word: " << wordDescription.englishWord << "\n";
    wordView << "Description:\n" << getDescription(wordDescription.description);
    return wordView.str();
}

std::string
DefaultWordViewFormatter::getDescription(const wordDescriptionRepository::Description& description) const
{
    std::stringstream wordDescriptionView;

    const auto& definitionsWithExamples = description.definitionsWithExamples;
    for (size_t index = 0; index < definitionsWithExamples.size() and index <= amountOfDefinitionsToView;
         ++index)
    {
        wordDescriptionView << "Definition: " << definitionsWithExamples[index].definition << "\n";
        if (const auto example = definitionsWithExamples[index].example)
        {
            wordDescriptionView << "Example: " << *example << "\n";
        }
    }

    const auto& sentences = description.sentences;
    for (size_t index = 0; index < sentences.size() and index <= amountOfSentencesToView; ++index)
    {
        wordDescriptionView << "Sentence: " << sentences[index] << "\n";
    }

    return wordDescriptionView.str();
}
}