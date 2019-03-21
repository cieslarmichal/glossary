#include "Word_Factory.h"

int main()
{
	try 
	{
		Word_Factory wf;
		Word w = wf.make_word(std::make_pair("fetch", "przyprowadzic"));


		for (auto x : w.get_description().definitions_examples)
		{
			std::cout << x.first<<std::endl;
			std::cout << x.second << std::endl;
		}
	}
	catch (std::exception& e) {
		std::cout << "exception: " << e.what() << std::endl;
	}
	catch (std::string & s)
	{
		std::cout << "exception: " << s << std::endl;
	}
	catch (const char * c)
	{
		std::cout << c << std::endl;
	}
	std::cin.get();
	return 0;
}
