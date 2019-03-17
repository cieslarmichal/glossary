#include "HTML_Reader.h"
#include "Parser.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>



int main()
{
	std::fstream file;
	file.open("code_to_parse.txt", std::ios::out);
	if (!file.good())
	{
		std::cout << "chujnia z txt\n";
	}

	//parser_v0(content);

	for (auto x : Parser::parser_v0((HTML_Reader::read_html("https://www.merriam-webster.com/dictionary/fetch"))))
	{
		//std::cout << x << std::endl << std::endl;
	}

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


