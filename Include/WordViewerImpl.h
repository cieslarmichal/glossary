#pragma once

#include "WordViewer.h"

class WordViewerImpl : public WordViewer
{
public:
    std::string viewWord(const WordDescription&) const override;
    std::string viewPolishWord(const EnglishWord&) const override;

private:
    std::string getWordDescription(const Description&) const;

    static size_t amountOfDefinitionsToView;
    static size_t amountOfSentencesToView;
};
