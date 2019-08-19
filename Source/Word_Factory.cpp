//#include "Word_Factory.h"
//
//std::unique_ptr<DatabaseImpl> Word_Factory::database(std::make_unique<DatabaseImpl>(DatabaseImpl()));
//
//std::vector<Word> Word_Factory::generate_words()
//{
//	std::vector<Word> words;
//
//	while (database->is_next_word())
//	{
//		words.push_back(make_word(database->read_word()));
//	}
//
//	return words;
//}
//
//Word Word_Factory::make_word(const std::pair<std::string, std::string> & eng_pl)
//{
//	Word_Description description;
//
//	std::pair<bool, bool> exist_and_descr(database->word_in_list(eng_pl.first));
//	bool exists = exist_and_descr.first;
//	bool description_txt = exist_and_descr.second;
//
//	std::cout << std::boolalpha;
//	std::cout << exists << " " << description_txt << std::endl;
//	if (exists)
//	{
//		if (description_txt)
//		{
//			std::cout << "E D" << std::endl;
//			description = database->read_description(eng_pl.first);
//		}
//		else
//		{
//			//default constructor
//			std::cout << "E ND" << std::endl;
//		}
//	}
//	else
//    {
////		std::cout << "NE" << std::endl;
////		std::vector<std::string> descr_test = HTML_Parser::filter_lines(eng_pl.first);
////		if ((descr_test.size() > 0) && (descr_test.at(0) != "not found"))
////		{
////			description = Word_Description(descr_test);
////			database->write_to_list(eng_pl.first, true);
////			database->write_to_glossary(eng_pl.first, description);
////		}
////		else
////		{
////			database->write_to_list(eng_pl.first, false);
////		}
////	}
//    }
//	return Word(eng_pl.first, eng_pl.second, description);
//}
