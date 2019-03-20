#include "Word.h"
#include <iostream>
#include "Glossary.h"

int main()
{
	//const Word w1("fetch", "");
	//Txt_File file("dictionary.txt");
	try 
	{
		Txt_File file("database/glossary.txt");
		//const Word w("fetch", "przyprowadzac", );

		//std::cout << w.get_english() << ": " << w.get_polish() << std::endl;

		//okej brak textu w glossary XD

		//Word_Description wd(Parser::parser_v0((HTML_Reader::read_html("https://www.merriam-webster.com/dictionary/"+std::string("fetch")))));

		//invalid string pos
		std::cout << "X";
		(Glossary::read_description(file.get_lines(), "fetch"));
		std::cout << "AFTER";
	}
	catch (std::exception& e) {
		std::cout << "exception: " << e.what() << std::endl;
	}

	/*for (auto def_eg : wd.definitions_examples)
	{
		std::cout << "def " << def_eg.first << std::endl;
		std::cout << "e.g. " << def_eg.second << std::endl;
		std::cout << std::endl;
	}

	for (auto s : wd.sentences)
	{
		std::cout << "sentence: " << s << std::endl;
		std::cout << std::endl;
	}*/

	//Glossary::operator<<(file, w1);

	//for (auto x : file.getLines())
	//{
	//	std::cout << x<<std::endl;
	//}
	std::cin.get();
	return 0;
}



	//std::regex reg("(<meta property=\"og:desc([^ ]+)?)");

	//print_matches(content, reg);
//void print_matches(std::string & str, std::regex reg)
//{
//	std::smatch matches;
//	std::cout << std::boolalpha;
//
//	while (std::regex_search(str, matches, reg))
//	{
//		std::cout << matches.ready() << std::endl;
//		std::cout << matches.str(1);
//		str = matches.suffix().str();
//		std::cout << std::endl;
//	}
//}


