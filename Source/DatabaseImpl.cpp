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

    auto startIndex = glossaryContent.find(englishWord +"\n{\n");
    if(startIndex==std::string::npos)
    {
        return boost::none;
    }
    auto endIndex = glossaryContent.find("}");

    auto lines = stringHelper::getSplitLines(stringHelper::substring(glossaryContent, startIndex, endIndex));
    return wordDescriptionParser.parse(lines);
}

void DatabaseImpl::writeWordExistenceInfo(const WordExistenceInfo &wordExistenceInfo) const
{
    fileAccess.append(wordExistenceInformationsFilePath, wordExistenceInfo.toString());
}


void DatabaseImpl::writeWordWithDescription(const EnglishWordWithDescription &word) const
{
    std::string toFile =  word.englishWord + "\n{\n";
    toFile+=word.wordDescription.toString() + "}\n";
    fileAccess.append(wordDescriptionsFilePath, toFile);
}
