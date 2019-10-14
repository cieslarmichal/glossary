#include "WordViewerImpl.h"

#include <sstream>

namespace
{

}

size_t WordViewerImpl::amountOfDefinitionsToView{5};
size_t WordViewerImpl::amountOfSentencesToView{2};

std::string WordViewerImpl::viewWord(const Word& word) const
{
    std::stringstream wordView;
    wordView << "English word: " << word.englishWord << "\n";
    wordView << "Polish translation: " << word.polishWord << "\n";
    wordView << getWordDescription(word.wordDescription);
    return wordView.str();
}

std::string WordViewerImpl::viewEnglishWord(const EnglishWord& englishWord) const
{
    std::stringstream wordView;
    wordView << "English word: " << englishWord << "\n";
    return wordView.str();
}

std::string WordViewerImpl::getWordDescription(const WordDescription& wordDescription) const
{
    std::stringstream wordDescriptionView;

    const auto& defsAndExmpls = wordDescription.definitionsWithExamples;
    for (size_t index = 0; index < defsAndExmpls.size() and index <= amountOfDefinitionsToView; ++index)
    {
        wordDescriptionView << "Definition: " << defsAndExmpls[index].definition << "\n";
        if (const auto example = defsAndExmpls[index].example)
        {
            wordDescriptionView << "Example: " << *example << "\n";
        }
    }

    const auto& sentences = wordDescription.sentences;
    for (size_t index = 0; index < sentences.size() and index <= amountOfSentencesToView; ++index)
    {
        wordDescriptionView << "Sentence: " << sentences[index] << "\n";

    }

    return wordDescriptionView.str();
}
