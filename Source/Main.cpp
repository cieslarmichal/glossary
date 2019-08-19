#include "Word_Factory.h"

#include "HtmlReaderImpl.h"
#include "GlossaryHtmlParser.h"
#include "FileAccessImpl.h"
#include "DatabaseImpl.h"

int main()
{
    FileAccessImpl fileAccess;
    DatabaseImpl database{fileAccess};
    auto x = database.readWordDescription("key");
    std::cout<<x->toString();
//    HtmlReaderImpl htmlReader;
//    auto htmlContent = (htmlReader.read("https://www.merriam-webster.com/dictionary/wine"));
//
//    fileAccess.write("../xxx", htmlContent);
//
//    GlossaryHtmlParser htmlParser;
//    for( auto x: htmlParser.parse(htmlContent))
//    {
//        std::cout<<x<<std::endl;
//    }

	return 0;
}
