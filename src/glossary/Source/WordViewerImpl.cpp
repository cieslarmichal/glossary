#include "WordViewerImpl.h"

#include <sstream>

size_t WordViewerImpl::amountOfDefinitionsToView{5};
size_t WordViewerImpl::amountOfSentencesToView{2};

std::string WordViewerImpl::viewWord(
    const Word& word) const
{
    std::stringstream wordView;
    wordView << "English word: " << word.englishWord<< "\n";
    wordView << "Polish word: " << word.polishWord << "\n";
    if(word.wordDescription)
    {
        wordView << getDescription(word.wordDescription->description);
    }
    return wordView.str();
}

std::string WordViewerImpl::viewPolishWord(const PolishWord& polishWord) const
{
    std::stringstream wordView;
    wordView << "Polish word: " << polishWord << "\n";
    return wordView.str();
}

std::string WordViewerImpl::getDescription(
    const wordsDescriptionsDb::Description& description) const
{
    // TODO: improve viewing: once definitions: and something like ":",
    // examples: "//", sentences: "sentence"
    std::stringstream wordDescriptionView;

    const auto& defsAndExmpls = description.definitionsWithExamples;
    for (size_t index = 0;
         index < defsAndExmpls.size() and index <= amountOfDefinitionsToView;
         ++index)
    {
        wordDescriptionView << "Definition: " << defsAndExmpls[index].definition
                            << "\n";
        if (const auto example = defsAndExmpls[index].example)
        {
            wordDescriptionView << "Example: " << *example << "\n";
        }
    }

    const auto& sentences = description.sentences;
    for (size_t index = 0;
         index < sentences.size() and index <= amountOfSentencesToView; ++index)
    {
        wordDescriptionView << "Sentence: " << sentences[index] << "\n";
    }

    return wordDescriptionView.str();
}
