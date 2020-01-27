#pragma once

#include "WordViewer.h"

class WordViewerImpl : public WordViewer
{
public:
    std::string viewWord(
        const wordsDb::wordsDescriptionsDb::WordDescription&) const override;
    std::string viewPolishWord(const EnglishWord&) const override;

private:
    std::string
    getDescription(const wordsDb::wordsDescriptionsDb::Description&) const;

    static size_t amountOfDefinitionsToView;
    static size_t amountOfSentencesToView;
};
