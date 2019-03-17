#include "Word.h"
#include <iostream>
#include "Txt_File.h"

int main()
{
	//Word w1("hence", "kostka");
	Txt_File file("dictionary.txt");

	for (auto x : file.getLines())
	{
		std::cout << x<<std::endl;
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


