#pragma once

#include "WordViewer.h"

class WordViewerImpl : public WordViewer
{
public:
    std::string
    viewWord(const wordsDb::descriptionsDb::WordDescription&) const override;
    std::string viewPolishWord(const EnglishWord&) const override;

private:
    std::string
    getWordDescription(const wordsDb::descriptionsDb::Description&) const;

    static size_t amountOfDefinitionsToView;
    static size_t amountOfSentencesToView;
};
