#include "Word_Factory.h"
#include "TextFileReader.h"
#include "HtmlFileReader.h"
#include "HTML_Parser.h"
#include "TextFileWriter.h"
#include "HtmlParserImpl.h"

int main()
{
//	try
//	{
//		for (auto & x : Word_Factory::generate_words())
//		{
//			std::cout << x.get_english()<<std::endl;
//			for (auto x : x.get_description().get_definitions_examples())
//			{
//				std::cout << "def: " << x.first << std::endl;
//				std::cout << "e.g. " << x.second << std::endl;
//			}
//			std::cout << std::endl << std::endl;
//		}
//
//	}
//	catch (std::exception& e) {
//		std::cout << "exception: " << e.what() << std::endl;
//	}
//	catch (std::string & s)
//	{
//		std::cout << "exception: " << s << std::endl;
//	}
//	catch (const char * c)
//	{
//		std::cout << c << std::endl;
//	}


    HtmlFileReader htmlFileReader;
    auto htmlContent = (htmlFileReader.read("https://www.merriam-webster.com/dictionary/fetch"));

    TextFileWriter textFileWriter;
    textFileWriter.write("../xxx", htmlContent);

    HtmlParserImpl htmlParser;
    for( auto x: htmlParser.parse(htmlContent))
    {
        std::cout<<x<<std::endl;
    }

	return 0;
}
