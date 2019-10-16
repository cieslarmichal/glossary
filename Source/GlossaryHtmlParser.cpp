#include "GlossaryHtmlParser.h"

#include "StringHelper.h"
#include "boost/algorithm/string.hpp"

namespace
{
void removeSpecialHtmlSequences(std::string&);

bool isDefinition(const std::string&);

bool isExample(const std::string&);

bool isSentence(const std::string&);

const std::string htmlDefinitionTag{R"(<span class="dtText"><strong class="mw_t_bc">: </strong>)"};
const std::string htmlSentenceTag{"<span class=\"t has-aq\">"};
const std::string htmlExampleTag1{"<span class=\"ex-sent first-child t no-aq sents\">"};
const std::string htmlExampleTag2{"<span class=\"ex-sent first-child t has-aq sents\">"};
const std::string exampleMark{"//"};
const std::string sentenceMark{"\""};
const std::vector<std::string> sequencesToDelete{"&mdash;", "&quot;"};

}

std::vector<std::string> GlossaryHtmlParser::parse(const std::string& htmlContent) const
{
    auto htmlContentLines = stringHelper::getSplitLines(htmlContent);

    auto importantLines = selectImportantLines(htmlContentLines);

    auto parsedContent = DefaultHtmlParser::parse(stringHelper::getJoinedLines(importantLines));

    removeHtmlStrings(parsedContent);

    return parsedContent;
}


std::vector<std::string> GlossaryHtmlParser::selectImportantLines(const std::vector<std::string>& htmlContent) const
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

void GlossaryHtmlParser::removeHtmlStrings(std::vector<std::string>& htmlContent) const
{
    for (auto& line : htmlContent)
    {
        removeSpecialHtmlSequences(line);
    }
}

namespace
{

void removeSpecialHtmlSequences(std::string& line)
{
    for (const auto& sequenceToDelete : sequencesToDelete)
    {
        boost::erase_all(line, sequenceToDelete);
    }
}

bool isDefinition(const std::string& line)
{
    return (line.find(htmlDefinitionTag) != std::string::npos);
}

bool isExample(const std::string& line)
{
    return ((line.find(htmlExampleTag1) != std::string::npos) || (line.find(htmlExampleTag2) != std::string::npos));
}

bool isSentence(const std::string& line)
{
    return (line.find(htmlSentenceTag) != std::string::npos);
}

}







