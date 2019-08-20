#include "DatabaseImpl.h"

#include "StringHelper.h"
#include <sstream>
#include <iostream>


namespace
{
bool isDefinition(const std::string &);

bool isExample(const std::string &);

bool isSentence(const std::string &);

const std::string dictionaryFilePath{"../database/dictionary.txt"};
const std::string glossaryFilePath{"../database/glossary.txt"};
const std::string existanceInformationsFilePath{"../database/list.txt"};
const std::string definitionMark{":"};
const std::string exampleMark{"//"};
const std::string sentenceMark{"\""};


}


DatabaseImpl::DatabaseImpl(FileAccess &access) : fileAccess(access), currentWordIndex{0}
{
    std::string dictionaryContent = fileAccess.readContent(dictionaryFilePath);
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

    std::string existanceInformations = fileAccess.readContent(existanceInformationsFilePath);

    for (const auto & line: stringHelper::getSplitLines(existanceInformations))
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

    return WordExistenceInfo({boost::none, descriptionExists});
}

void DatabaseImpl::appendWordExistenceInfo(const WordExistenceInfo &wordExistenceInfo) const
{
    fileAccess.append(existanceInformationsFilePath, wordExistenceInfo.toString());
}

boost::optional<WordDescription> DatabaseImpl::readWordDescription(const std::string &englishWord) const
{
    WordDescription wordDescription;
    std::string definition;
    std::string line;

    bool allowRead = false;

    std::string glossaryContent = fileAccess.readContent(glossaryFilePath);
    for (const auto & line : stringHelper::getSplitLines(glossaryContent))
    {
        std::cout << line << std::endl;
        if (line == ("$" + englishWord))
        {
            allowRead = true;
            continue;
        }

        if (!allowRead)
        {
            continue;
        }

        if (isDefinition(line))
        {
            definition = line;
        }

        if(isExample(line))
        {
            wordDescription.definitionsWithExamples.emplace_back(std::make_pair(definition, line));
        }

        if(isSentence(line))
        {
            wordDescription.sentences.push_back(line);
        }
    }

    return wordDescription;
}

void DatabaseImpl::writeWordDescription(const std::string &englishWord, const WordDescription &description) const
{
    std::string contentToWrite = "$" + englishWord + "\n" + description.toString();
    fileAccess.append(glossaryFilePath, contentToWrite);
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





