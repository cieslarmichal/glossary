#include "DatabaseImpl.h"

#include "StringHelper.h"
#include <sstream>
#include <iostream>

namespace
{
bool isDefinition(const std::string &);

bool isExample(const std::string &);

bool isSentence(const std::string &);

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

boost::optional<WordExistenceInfo> DatabaseImpl::getWordExistenceInfo(const std::string &expectedEnglishWord) const
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

boost::optional<WordDescription> DatabaseImpl::getWordDescription(const std::string &englishWord) const
{
    WordDescription wordDescription{englishWord};

    std::string glossaryContent = fileAccess.readContent(wordDescriptionsFilePath);


    std::string definition;
    bool allowRead = false;

    for (const auto &line : stringHelper::getSplitLines(glossaryContent))
    {
        if (line == ("$" + englishWord))
        {
            allowRead = true;
            continue;
        }

        if (!allowRead)
        {
            continue;
        }

        if (!line.empty() && line.at(0) == '$' && allowRead)
        {
            break;
        }

        if (isDefinition(line))
        {
            definition = line;
        }

        if (isExample(line))
        {
            wordDescription.definitionsWithExamples.emplace_back(std::make_pair(definition, line));
        }

        if (isSentence(line))
        {
            wordDescription.sentences.push_back(line);
        }
    }

    return (!wordDescription.definitionsWithExamples.empty()) ? boost::optional<WordDescription>(wordDescription)
                                                              : boost::none;
}

void DatabaseImpl::writeWordExistenceInfo(const WordExistenceInfo &wordExistenceInfo) const
{
    fileAccess.append(wordExistenceInformationsFilePath, wordExistenceInfo.toString());
}


void DatabaseImpl::writeWordDescription(const WordDescription &description) const
{
    fileAccess.append(wordDescriptionsFilePath, description.toString());
}


namespace
{

bool isDefinition(const std::string &line)
{
    return ((line.size() >= definitionMark.size()) && (line.substr(0, 1) == definitionMark));
}

bool isExample(const std::string &line)
{
    return ((line.size() >= exampleMark.size()) && (line.substr(0, 2) == exampleMark));
}

bool isSentence(const std::string &line)
{
    return ((line.size() >= sentenceMark.size()) && (line.substr(0, 1) == sentenceMark));

}

}





