#include "HtmlParserImpl.h"

#include <sstream>
#include <iostream>


namespace
{
bool isDefinition(const std::string &line);

bool isExample(const std::string &line);

bool isSentence(const std::string &line);

const std::string htmlDefinitionTag{"<span class=\"dtText\"><strong class=\"mw_t_bc\">: </strong>"};
const std::string htmlSentenceTag{"<span class=\"t has-aq\">"};
const std::string htmlExampleTag1{"<span class=\"ex-sent first-child t no-aq sents\">"};
const std::string htmlExampleTag2{"<span class=\"ex-sent first-child t has-aq sents\">"};
const std::string definitionMark{"~definition"};
const std::string exampleMark{"~example"};
const std::string sentenceMark{"~sentence"};
}

std::vector<std::string> HtmlParserImpl::parse(const std::string &htmlContent) const
{
    return selectImportantLines(htmlContent);
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
            line += definitionMark;
            importantLines.push_back(line);
        }
        else if (isExample(line))
        {
            line += exampleMark;
            importantLines.push_back(line);
        }
        else if (isSentence(line))
        {
            line += sentenceMark;
            importantLines.push_back(line);
        }
    }

    return importantLines;
}

std::string HtmlParserImpl::removeHtmlTags(const std::string &) const
{
//    std::string result{ str };
//
//    size_t open_sign_pos = result.find("<");
//    size_t close_sign_pos = result.find(">");
//
//    while ((open_sign_pos != std::string::npos) && (close_sign_pos != std::string::npos))
//    {
//        result = String_Additives::cut_off_string(result, open_sign_pos, close_sign_pos);
//        open_sign_pos = result.find("<");
//        close_sign_pos = result.find(">");
//    }
//
//    open_sign_pos = result.find("&mdash;");
//    while (open_sign_pos != std::string::npos)
//    {
//        result = String_Additives::cut_off_string(result, open_sign_pos, open_sign_pos + 6);
//        open_sign_pos = result.find("&mdash;");
//    }
//
//    open_sign_pos = result.find("&quot;");
//    while (open_sign_pos != std::string::npos)
//    {
//        result.at(open_sign_pos) = '\"';
//        result = String_Additives::cut_off_string(result, open_sign_pos + 1, open_sign_pos + 5);
//        open_sign_pos = result.find("&quot;");
//    }
//
//    String_Additives::trim(result);
//
//    return result;
}


namespace
{

bool isDefinition(const std::string &line)
{
    return (line.find(htmlDefinitionTag) != std::string::npos);
}

bool isExample(const std::string &line)
{
    return ((line.find(htmlExampleTag1) != std::string::npos) || (line.find(htmlExampleTag2) != std::string::npos));
}

bool isSentence(const std::string &line)
{
    return (line.find(htmlSentenceTag) != std::string::npos);
}

}




