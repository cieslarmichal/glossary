#include "Word_Description.h"

Word_Description::Word_Description(std::vector<std::string> inp)
{
	clean_input(inp);
	for (auto x : inp)
	{
		std::cout << x << std::endl;
	}
	split_input(inp);
}

void Word_Description::clean_input(std::vector<std::string> & inp)
{
	std::vector<std::string> key_words{ "~eg" ,"~sentence" };

	inp.erase(std::remove_if(inp.begin(), inp.end(), [key_words](std::string line) 
		{return ((line == "") || (line == key_words.at(1)) || line==key_words.at(0)); }), inp.end());
}

void Word_Description::split_input(const std::vector<std::string> & inp)
{

}
