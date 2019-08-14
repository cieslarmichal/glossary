#include "Word_Factory.h"

#include "HtmlReaderImpl.h"
#include "GlossaryHtmlParser.h"
#include "FileAccessImpl.h"

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


    HtmlReaderImpl htmlReader;
    auto htmlContent = (htmlReader.read("https://www.merriam-webster.com/dictionary/wine"));

    FileAccessImpl fileAccess;
    fileAccess.write("../xxx", htmlContent);

    GlossaryHtmlParser htmlParser;
    for( auto x: htmlParser.parse(htmlContent))
    {
        std::cout<<x<<std::endl;
    }

	return 0;
}
