#pragma once

#include "WordViewer.h"

class WordViewerImpl : public WordViewer
{
public:
    std::string viewWord(const Word&) const override;
    std::string viewEnglishWord(const EnglishWord &) const override;

private:
    std::string getWordDescription(const WordDescription&) const;

    static size_t amountOfDefinitionsToView;
    static size_t amountOfSentencesToView;
};
