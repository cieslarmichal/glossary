#include "HtmlParserImpl.h"

#include "boost/algorithm/string.hpp"
#include <iostream>

namespace
{

void removeHtmlTags(std::string &);

void removeSpecialHtmlSequences(std::string &);

bool isDefinition(const std::string &);

bool isExample(const std::string &);

bool isSentence(const std::string &);

bool containsOpenHtmlTag(const std::string &);

bool containsCloseHtmlTag(const std::string &);

size_t findOpenHtmlTag(const std::string &);

size_t findCloseHtmlTag(const std::string &);

std::string cutOffFromString(const std::string &, size_t, size_t);

const std::string htmlDefinitionTag{"<span class=\"dtText\"><strong class=\"mw_t_bc\">: </strong>"};
const std::string htmlSentenceTag{"<span class=\"t has-aq\">"};
const std::string htmlExampleTag1{"<span class=\"ex-sent first-child t no-aq sents\">"};
const std::string htmlExampleTag2{"<span class=\"ex-sent first-child t has-aq sents\">"};
const std::string exampleMark{"//"};
const std::string sentenceMark{"\""};
const std::string openHtmlTag{"<"};
const std::string closeHtmlTag{">"};
const std::string endOfLine("\n");
const std::vector<std::string> sequencesToDelete{"&mdash;", "&quot;"};

}

std::vector<std::string> HtmlParserImpl::parse(const std::string &htmlContent) const
{
    std::vector<std::string> htmlContentLines;
    boost::split(htmlContentLines, htmlContent, boost::is_any_of(endOfLine));

    auto parsedContent = selectImportantLines(htmlContentLines);

    removeHtmlStrings(parsedContent);

    return parsedContent;
}

std::vector<std::string> HtmlParserImpl::selectImportantLines(const std::vector<std::string> &htmlContent) const
{
    std::vector<std::string> importantLines;

    for (auto line : htmlContent)
    {
        if (isDefinition(line))
        {
            line = boost::algorithm::trim_copy(line);
            importantLines.push_back(line);
        }
        else if (isExample(line))
        {
            line = exampleMark + boost::algorithm::trim_copy(line);
            importantLines.push_back(line);
        }
        else if (isSentence(line))
        {
            line = sentenceMark + boost::algorithm::trim_copy(line) + sentenceMark;
            importantLines.push_back(line);
        }
    }

    return importantLines;
}

void HtmlParserImpl::removeHtmlStrings(std::vector<std::string> & htmlContent) const
{
    for (auto & line : htmlContent)
    {
        removeHtmlTags(line);
        removeSpecialHtmlSequences(line);
    }
}

namespace
{

void removeHtmlTags(std::string &line)
{
    while (containsOpenHtmlTag(line) && containsCloseHtmlTag(line))
    {
        auto openSignPosition = findOpenHtmlTag(line);
        auto closeSignPosition = findCloseHtmlTag(line);
        line = cutOffFromString(line, openSignPosition, closeSignPosition);
    }
}

void removeSpecialHtmlSequences(std::string &line)
{
    for (const auto sequenceToDelete : sequencesToDelete)
    {
        boost::erase_all(line, sequenceToDelete);
    }
}

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

bool containsOpenHtmlTag(const std::string &line)
{
    return (line.find(openHtmlTag) != std::string::npos);
}

bool containsCloseHtmlTag(const std::string &line)
{
    return (line.find(closeHtmlTag) != std::string::npos);
}

size_t findOpenHtmlTag(const std::string &line)
{
    return line.find(openHtmlTag);
}

size_t findCloseHtmlTag(const std::string &line)
{
    return line.find(closeHtmlTag);
}

std::string cutOffFromString(const std::string &line, size_t startIndexToCut, size_t endIndexToCut)
{
    auto sizeOfLine = line.size();

    auto head = line.substr(0, startIndexToCut);
    auto tail = line.substr(endIndexToCut + 1, sizeOfLine - endIndexToCut);

    return head + tail;
}

}







