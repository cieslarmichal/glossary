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

private:
    std::unique_ptr<Word> createWord(const WordWithTranslation &);

	std::shared_ptr<Database> database;
	std::shared_ptr<HtmlReader> htmlReader;
	std::shared_ptr<HtmlParser> htmlParser;
	WordDescriptionParser wordDescriptionParser;
};

