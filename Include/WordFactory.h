#pragma once

#include <memory>

#include "Database.h"
#include "HtmlReader.h"
#include "HtmlParser.h"
#include "Word.h"
#include "WordWithTranslation.h"
#include "WordDescriptionParser.h"

class WordFactory
{
public:
    explicit WordFactory(std::shared_ptr<Database>);

    std::unique_ptr<Word> createWord(const WordWithTranslation &);
private:

	std::shared_ptr<Database> database;
	std::unique_ptr<HtmlReader> htmlReader;
	std::unique_ptr<HtmlParser> htmlParser;
	WordDescriptionParser wordDescriptionParser;
};

