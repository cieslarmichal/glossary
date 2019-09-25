#include "DatabaseImpl.h"

#include "StringHelper.h"
#include <sstream>
#include <iostream>

namespace
{
const std::string wordTranslationsFilePath{"../database/dictionary.txt"};
const std::string wordDescriptionsFilePath{"../database/glossary.txt"};
const std::string wordExistenceInformationsFilePath{"../database/list.txt"};
const std::string definitionMark{":"};
const std::string exampleMark{"//"};
const std::string sentenceMark{"\""};
}


DatabaseImpl::DatabaseImpl(FileAccess &access) : fileAccess(access), currentWordIndex{0}
{
    std::string dictionaryContent = fileAccess.readContent(wordTranslationsFilePath);
    dictionaryWords = stringHelper::getSplitLines(dictionaryContent);
}


boost::optional<WordWithTranslation> DatabaseImpl::readNextWord() const
{
    if (!nextWordExists())
    {
        return boost::none;
    }

    std::stringstream line(dictionaryWords.at(currentWordIndex));
    std::string english, polish;

    line >> english >> polish;
    currentWordIndex++;

    return WordWithTranslation{english, polish};
}

bool DatabaseImpl::nextWordExists() const
{
    return (currentWordIndex < dictionaryWords.size() &&
            !dictionaryWords.at(currentWordIndex).empty());
}

boost::optional<WordExistenceInfo> DatabaseImpl::getWordExistenceInfo(const EnglishWord &expectedEnglishWord) const
{
    bool descriptionExists = false;

    std::string existenceInformations = fileAccess.readContent(wordExistenceInformationsFilePath);

    for (const auto &line: stringHelper::getSplitLines(existenceInformations))
    {
        std::stringstream lineStream{line};
        std::string word;
        lineStream >> word;
        if (word == expectedEnglishWord)
        {
            lineStream >> descriptionExists;
            return WordExistenceInfo({expectedEnglishWord, descriptionExists});
        }
    }

    return boost::none;
}

boost::optional<WordDescription> DatabaseImpl::getWordDescription(const EnglishWord &englishWord) const
{
    std::string glossaryContent = fileAccess.readContent(wordDescriptionsFilePath);

    auto startIndex = glossaryContent.find("$" + englishWord);
    if(startIndex!=std::string::npos)
    {
        auto endIndex = glossaryContent.find("$")
    }
    bool allowRead = false;

    std::vector<std::string> lines;
    for (const auto &line : stringHelper::getSplitLines(glossaryContent))
    {
        if (line == ("$" + englishWord))
        {
            allowRead = true;
            continue;
        }

        if (allowRead)
        {
            lines.push_back(line);
        }
    }


    if(not lines.empty())
    {
        return wordDescriptionParser.parse(lines);
    }
    return boost::none;
}

void DatabaseImpl::writeWordExistenceInfo(const WordExistenceInfo &wordExistenceInfo) const
{
    fileAccess.append(wordExistenceInformationsFilePath, wordExistenceInfo.toString());
}


void DatabaseImpl::writeWordDescription(const WordDescription &description) const
{
    fileAccess.append(wordDescriptionsFilePath, description.toString());
}
