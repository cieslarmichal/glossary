#include "HtmlDescriptionLinesSelector.h"

#include <map>

#include "utils/HtmlTagsDeleter.h"
#include "utils/StringHelper.h"

namespace glossary::wordDescriptionDownloader
{
namespace
{
// TODO: synonyms  starts with <ul class="mw-list">, ends with </ul>
struct TagWithPosition;
bool operator<(const TagWithPosition& ls, const TagWithPosition& rs);
std::vector<std::string> getTagsContent(const std::string& content);
bool containsAnyTagWithEndTag(const std::string& content);
bool containsTagWithEndTag(const std::string& content, const std::string& tag);
TagWithPosition findNearestEndTagPosition(const std::string& content, size_t startTagPosition);
TagWithPosition findNearestTagPosition(const std::string& content);
std::vector<TagWithPosition> getGlossaryTagsWithPositions(const std::string& content,
                                                          size_t startPosition = 0);
TagWithPosition getTagPositionWithLowestPosition(const std::vector<TagWithPosition>& tagsWithPositions);

const std::string htmlDefinitionTag{R"(<span class="dtText"><strong class="mw_t_bc">)"};
const std::string htmlSentenceTag1{"<span class=\"t has-aq\">"};
const std::string htmlSentenceTag2{"<span class=\"ex-sent  t no-aq sents\">"};
const std::string htmlExampleTag1{"<span class=\"ex-sent first-child t no-aq sents\">"};
const std::string htmlExampleTag2{"<span class=\"ex-sent first-child t has-aq sents\">"};
const std::string htmlExampleTag3{"<span class=\"ex-sent first-child t no-aq sents\">"};
const std::string htmlEndTag{R"(</span>)"};
const std::string htmlFindProlongationTag1{"<span class=\"mw_t_wi\">"};
const std::string htmlFindProlongationTag2{"<span class=\"text-uppercase\">"};

const std::string examplePrefix{"// "};
const std::string sentencePrefix{"; "};
std::map<std::string, std::string> tagPrefixMapping = {{htmlExampleTag1, examplePrefix},
                                                       {htmlExampleTag2, examplePrefix},
                                                       {htmlExampleTag3, examplePrefix},
                                                       {htmlSentenceTag1, sentencePrefix},
                                                       {htmlSentenceTag2, sentencePrefix}};
}

HtmlDescriptionLinesSelector::HtmlDescriptionLinesSelector()
    : htmlTagsDeleter{std::make_unique<utils::HtmlTagsDeleter>()}
{
}

std::vector<std::string> HtmlDescriptionLinesSelector::selectLines(const std::string& htmlContent) const
{
    const auto glossaryLines = selectGlossaryLines(htmlContent);
    auto parsedContent = htmlTagsDeleter->deleteTags(glossaryLines);
    return parsedContent;
}

std::vector<std::string>
HtmlDescriptionLinesSelector::selectGlossaryLines(const std::string& htmlContent) const
{
    return getTagsContent(htmlContent);
}

namespace
{
struct TagWithPosition
{
    std::string tag;
    size_t position{};

    std::string getPrefix() const
    {
        if (tagPrefixMapping.count(tag))
        {
            return tagPrefixMapping.at(tag);
        }
        return {};
    }
};

bool operator<(const TagWithPosition& ls, const TagWithPosition& rs)
{
    return ls.position < rs.position;
}

std::vector<std::string> getTagsContent(const std::string& contentInit)
{
    std::vector<std::string> tagsContent;

    auto content{contentInit};
    while (containsAnyTagWithEndTag(content))
    {
        const auto startTagWithPosition = findNearestTagPosition(content);
        if (startTagWithPosition.position + 1 < content.size())
        {
            const auto endTagPos = findNearestEndTagPosition(content, startTagWithPosition.position);
            if (endTagPos.position != std::string::npos)
            {
                auto tagContent =
                    utils::substring(content, startTagWithPosition.position + startTagWithPosition.tag.size(),
                                     endTagPos.position);
                utils::trim(tagContent);
                const auto contentWithPrefix = startTagWithPosition.getPrefix() + tagContent;
                tagsContent.push_back(contentWithPrefix);
                content = content.substr(endTagPos.position);
            }
        }
    }

    return tagsContent;
}

bool containsAnyTagWithEndTag(const std::string& content)
{
    const auto containsDefinitionTag = containsTagWithEndTag(content, htmlDefinitionTag);
    const auto containsExample1Tag = containsTagWithEndTag(content, htmlExampleTag1);
    const auto containsExample2Tag = containsTagWithEndTag(content, htmlExampleTag2);
    const auto containsExample3Tag = containsTagWithEndTag(content, htmlExampleTag3);
    const auto containsSentenceTag1 = containsTagWithEndTag(content, htmlSentenceTag1);
    const auto containsSentenceTag2 = containsTagWithEndTag(content, htmlSentenceTag2);
    return containsDefinitionTag || containsExample1Tag || containsExample2Tag || containsExample3Tag ||
           containsSentenceTag1 || containsSentenceTag2;
}

bool containsTagWithEndTag(const std::string& content, const std::string& tag)
{
    const auto tagPosition = content.find(tag);
    if (tagPosition != std::string::npos && tagPosition + 1 < content.size())
    {
        const auto nearestEndTag = findNearestEndTagPosition(content, tagPosition);
        return nearestEndTag.position != std::string::npos;
    }
    return false;
}

TagWithPosition findNearestEndTagPosition(const std::string& content, size_t startTagPosition)
{
    TagWithPosition prolongation1{htmlFindProlongationTag1,
                                  content.find(htmlFindProlongationTag1, startTagPosition + 1)};
    TagWithPosition prolongation2{htmlFindProlongationTag2,
                                  content.find(htmlFindProlongationTag2, startTagPosition + 1)};
    TagWithPosition end{htmlEndTag, content.find(htmlEndTag, startTagPosition + 1)};
    while ((prolongation1.position < end.position || prolongation2.position < end.position) &&
           end.position != std::string::npos)
    {
        prolongation1 = {htmlFindProlongationTag1,
                         content.find(htmlFindProlongationTag1, prolongation1.position + 1)};
        prolongation2 = {htmlFindProlongationTag2,
                         content.find(htmlFindProlongationTag2, prolongation2.position + 1)};
        end = {htmlEndTag, content.find(htmlEndTag, end.position + 1)};
    }

    auto tagsWithPositions = getGlossaryTagsWithPositions(content, startTagPosition + 1);
    tagsWithPositions.emplace_back(end);

    return getTagPositionWithLowestPosition(tagsWithPositions);
}

TagWithPosition findNearestTagPosition(const std::string& content)
{
    const auto tagsWithPositions = getGlossaryTagsWithPositions(content);
    return getTagPositionWithLowestPosition(tagsWithPositions);
}

std::vector<TagWithPosition> getGlossaryTagsWithPositions(const std::string& content, size_t startPosition)
{
    const TagWithPosition definition{htmlDefinitionTag, content.find(htmlDefinitionTag, startPosition)};
    const TagWithPosition example1{htmlExampleTag1, content.find(htmlExampleTag1, startPosition)};
    const TagWithPosition example2{htmlExampleTag2, content.find(htmlExampleTag2, startPosition)};
    const TagWithPosition example3{htmlExampleTag3, content.find(htmlExampleTag3, startPosition)};
    const TagWithPosition sentence1{htmlSentenceTag1, content.find(htmlSentenceTag1, startPosition)};
    const TagWithPosition sentence2{htmlSentenceTag2, content.find(htmlSentenceTag2, startPosition)};
    return {definition, example1, example2, example3, sentence1, sentence2};
}

TagWithPosition getTagPositionWithLowestPosition(const std::vector<TagWithPosition>& tagsWithPositions)
{
    TagWithPosition tagWithLowestPosition{tagsWithPositions[0]};
    tagWithLowestPosition.position = std::string::npos;

    for (const auto& tagWithPosition : tagsWithPositions)
    {
        if (tagWithPosition < tagWithLowestPosition)
            tagWithLowestPosition = tagWithPosition;
    }
    return tagWithLowestPosition;
}

}
}
