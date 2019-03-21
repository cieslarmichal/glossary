#include "Word_Factory.h"
#include "Database.h"
#include "Word.h"


Word_Factory::Word_Factory()
{
	database = std::make_unique<Database>(Database());
}

Word Word_Factory::make_word(const std::pair<std::string, std::string> & eng_pl)
{
	Word_Description description;

	std::pair<bool, bool> exist_and_descr(database->word_in_list(eng_pl.first));
	bool exists = exist_and_descr.first;
	bool description_txt = exist_and_descr.second;

	std::cout << std::boolalpha;
	std::cout << exists << " " << description_txt << std::endl;
	if (exists)
	{
		if (description_txt)
		{
			std::cout << "E D" << std::endl;
			description = database->read_description(eng_pl.first);
		}
		else
		{
			//default constructor
			std::cout << "E ND" << std::endl;

		}
	}
	else
	{
		std::cout << "NE" << std::endl;

		database->write_to_list(eng_pl.first, true);
		description = Word_Description(HTML_Reader::read_html(eng_pl.first));
		database->write_to_glossary(eng_pl.first, description);
	}

	return Word(eng_pl.first, eng_pl.second, description);
}
