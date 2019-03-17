#include "HTML_Reader.h"
#include "Parser.h"
#include "Word_Description.h"


int main()
{
	Word_Description wd(Parser::parser_v0((HTML_Reader::read_html("https://www.merriam-webster.com/dictionary/keyboard"))));
	


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


