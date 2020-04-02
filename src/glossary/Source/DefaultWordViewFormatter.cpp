#include "DefaultWordViewFormatter.h"

#include <sstream>

namespace glossary
{
size_t DefaultWordViewFormatter::amountOfDefinitionsToView{5};
size_t DefaultWordViewFormatter::amountOfSentencesToView{2};

std::string DefaultWordViewFormatter::formatWordView(const Word& word) const
{
    std::stringstream wordView;
    wordView << "English word: " << word.englishWord << "\n";
    if (word.polishTranslation)
    {
        wordView << "Polish translation: " << *word.polishTranslation << "\n";
    }
    if (word.wordDescription)
    {
        wordView << getDescription(word.wordDescription->description);
    }
    return wordView.str();
}

std::string DefaultWordViewFormatter::formatPolishWordView(const PolishWord& polishWord) const
{
    std::stringstream wordView;
    wordView << "Polish word: " << polishWord << "\n";
    return wordView.str();
}

std::string
DefaultWordViewFormatter::getDescription(const wordDescriptionRepository::Description& description) const
{
    std::stringstream wordDescriptionView;

    const auto& defsAndExmpls = description.definitionsWithExamples;
    for (size_t index = 0; index < defsAndExmpls.size() and index <= amountOfDefinitionsToView; ++index)
    {
        wordDescriptionView << "Definition: " << defsAndExmpls[index].definition << "\n";
        if (const auto example = defsAndExmpls[index].example)
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