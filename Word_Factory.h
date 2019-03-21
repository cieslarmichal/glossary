#pragma once
#include "Database.h"
#include "HTML_Reader.h"
#include "Word.h"

class Word_Factory
{
public:
	Word_Factory();
	Word make_word(const std::pair<std::string, std::string> &);
private:
	std::unique_ptr<Database> database;
};

