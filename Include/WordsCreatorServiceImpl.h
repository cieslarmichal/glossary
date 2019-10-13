#pragma once

#include "WordsCreatorService.h"

#include "DictionaryReader.h"
#include "DictionaryAvailabilityHandler.h"
#include "Database.h"
#include "HtmlWordsCreator.h"

#include <memory>

class WordsCreatorServiceImpl : public WordsCreatorService
{
public:
    WordsCreatorServiceImpl();

    Words createWords() const override;

private:
    void initializeWordsCreatorService();
    void initializeDictionary();

    std::unique_ptr<const Database> wordsDb;
    std::unique_ptr<const HtmlWordsCreator> htmlWordCreator;
    std::unique_ptr<const DictionaryReader> dictionaryReader;
    std::unique_ptr<const DictionaryAvailabilityHandler> availabilityHandler;

    Dictionary dictionary;
    DictionaryAvailability dictionaryAvailability;
};