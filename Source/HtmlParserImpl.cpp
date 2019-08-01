#include "HtmlParserImpl.h"

#include "boost/algorithm/string/trim.hpp"
#include <sstream>
#include <iostream>


namespace
{
const std::string htmlDefinitionTag{"<span class=\"dtText\"><strong class=\"mw_t_bc\">: </strong>"};
const std::string htmlSentenceTag{"<span class=\"t has-aq\">"};
const std::string htmlExampleTag1{"<span class=\"ex-sent first-child t no-aq sents\">"};
const std::string htmlExampleTag2{"<span class=\"ex-sent first-child t has-aq sents\">"};
const std::string exampleMark{"//"};
const std::string sentenceMark{"\""};
const std::string openHtmlTag{"<"};
const std::string closeHtmlTag{">"};
}

std::vector<std::string> HtmlParserImpl::parse(const std::string &htmlContent) const
{
    std::vector<std::string> importantLinesFromHtmlContent = selectImportantLines(htmlContent);

    return importantLinesFromHtmlContent;
}

std::vector<std::string> HtmlParserImpl::selectImportantLines(const std::string &content) const
{
    std::vector<std::string> importantLines;

    std::stringstream htmlContent{content};
    std::string line;

    while (std::getline(htmlContent, line))
    {
        if (isDefinition(line))
        {
            line = boost::algorithm::trim_copy(line);
            importantLines.push_back(removeHtmlTags(line));
        }
        else if (isExample(line))
        {
            line = exampleMark + boost::algorithm::trim_copy(line);
            importantLines.push_back(removeHtmlTags(line));
        }
        else if (isSentence(line))
        {
            line = sentenceMark + boost::algorithm::trim_copy(line) + sentenceMark;
            importantLines.push_back(removeHtmlTags(line));
        }
    }

    return importantLines;
}

std::string cutOffFromString(const std::string & line, size_t startIndexToCut, size_t endIndexToCut)
{
    auto sizeOfLine = line.size();
    if ((startIndexToCut > sizeOfLine - 1) || (sizeOfLine - endIndexToCut < 0))
    {
        throw "cutOffFromString: bad indices";
    }

    auto head =  line.substr(0, startIndexToCut);
    auto tail = line.substr(endIndexToCut + 1, sizeOfLine - endIndexToCut);

    return head + tail;
}

std::string HtmlParserImpl::removeHtmlTags(const std::string & line) const
{
    std::string result{ line };

    auto openSignPosition = result.find(openHtmlTag);
    auto closeSignPosition = result.find(closeHtmlTag);

    while ((openSignPosition != std::string::npos) && (closeSignPosition != std::string::npos))
    {
        result = cutOffFromString(result, openSignPosition, closeSignPosition);
        openSignPosition = result.find(openHtmlTag);
        closeSignPosition = result.find(closeHtmlTag);
    }


    auto specialSignPosition = result.find("&mdash;");
    while (specialSignPosition != std::string::npos)
    {
        result = cutOffFromString(result, specialSignPosition, specialSignPosition + 6);
        specialSignPosition = result.find("&mdash;");
    }

    specialSignPosition = result.find("&quot;");
    while (specialSignPosition != std::string::npos)
    {
        result.at(specialSignPosition) = '\"';
        result = cutOffFromString(result, specialSignPosition + 1, specialSignPosition + 5);
        specialSignPosition = result.find("&quot;");
    }


    return result;
}


bool HtmlParserImpl::isDefinition(const std::string &line) const
{
    return (line.find(htmlDefinitionTag) != std::string::npos);
}

bool HtmlParserImpl::isExample(const std::string &line) const
{
    return ((line.find(htmlExampleTag1) != std::string::npos) || (line.find(htmlExampleTag2) != std::string::npos));
}

bool HtmlParserImpl::isSentence(const std::string &line) const
{
    return (line.find(htmlSentenceTag) != std::string::npos);
}






