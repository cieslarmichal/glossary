#include "Word_Factory.h"

#include "HtmlReaderImpl.h"
#include "GlossaryHtmlParser.h"
#include "FileAccessImpl.h"
#include "DatabaseImpl.h"
#include "StringHelper.h"
#include "WordDescription.h"

#include <iostream>

int main()
{
    FileAccessImpl fileAccess;
    DatabaseImpl database{fileAccess};
    HtmlReaderImpl htmlReader;
    auto htmlContent = (htmlReader.read("https://www.merriam-webster.com/dictionary/wine"));


    GlossaryHtmlParser htmlParser;
    auto parsedContent = htmlParser.parse(htmlContent);
    fileAccess.write("../xxx", stringHelper::getJoinedLines(parsedContent));

    WordDescription wd(parsedContent);

    std::cout<<wd.toString();


	return 0;
}
