#include "DatabaseImpl.h"

#include "StringHelper.h"
#include <sstream>


namespace
{
const std::string dictionaryFilePath{"../database/dictionary.txt"};
const std::string glossaryFilePath{"../database/glossary.txt"};
const std::string existanceInformationsFilePath{"../database/list.txt"};
const std::string definitionMark{":"};
const std::string exampleMark{"//"};
const std::string sentenceMark{"\""};

}


DatabaseImpl::DatabaseImpl(FileAccess & access) :fileAccess(access), currentWordIndex{0}
{
    std::string dictionaryContent = fileAccess.readContent(dictionaryFilePath);
	dictionaryWords = getSplitLines(dictionaryContent);
}

//bool DatabaseImpl::is_line_word(const std::string & line) const
//{
//	for (auto c : line)
//	{
//		if (!isspace(c))
//		{
//			return true;
//		}
//	}
//	return false;
//}

boost::optional<WordWithTranslation> DatabaseImpl::readNextWord() const
{
    if(!nextWordExists())
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

boost::optional<WordExistenceInfo> DatabaseImpl::getWordExistenceInfo(const std::string & expectedEnglishWord) const
{
    bool descriptionExists = false;

    std::string existanceInformations = fileAccess.readContent(existanceInformationsFilePath);

    for (auto line: getSplitLines(existanceInformations))
    {
        std::stringstream lineStream{line};
        std::string word;
        lineStream >> word;
        if(word == expectedEnglishWord)
        {
			lineStream >> descriptionExists;
            return WordExistenceInfo({expectedEnglishWord, descriptionExists});
        }
    }

    return WordExistenceInfo({boost::none, descriptionExists});
}

void DatabaseImpl::appendWordExistenceInfo(const WordExistenceInfo & wordExistenceInfo) const
{
    fileAccess.append(existanceInformationsFilePath, wordExistenceInfo.toString());
}

boost::optional<WordDescription> DatabaseImpl::readWordDescription(const std::string & englishWord) const
{
    WordDescription wordDescription;
	std::string def, eg, sentc;
	std::string line;

	bool allow_read = false;
	bool eg_next = false;

	std::string glossaryContent = fileAccess.readContent(glossaryFilePath);
	for (auto line : getSplitLines(glossaryContent))
    {
	    std::cout<<line<<std::endl;
        if (line == ("$" + englishWord))
        {
            allow_read = true;
            continue;
        }

        if(!allow_read) continue;

        if ((line.size() >= definitionMark.size()) && (line.substr(0, 1) == definitionMark))
        {
            def = line;
            //eg_next = true;
        }

        if ((line.size() >= exampleMark.size()) && (line.substr(0, 2) == exampleMark))
        {
            //eg = cutOffFromString(line, 0, 2);
            wordDescription.definitionsWithExamples.emplace_back(std::make_pair(def, line));
        }

        if ((line.size() >= sentenceMark.size()) && (line.substr(0, 1) == sentenceMark))
        {
            //sentc = cutOffFromString(line, 0, 2);
            wordDescription.sentences.push_back(sentc);
        }
    }

    return wordDescription;
}

void DatabaseImpl::writeWordDescription(const std::string & englishWord, const WordDescription & description) const
{
    std::string contentToWrite = "$" + englishWord + "\n" + description.toString();
    fileAccess.append(glossaryFilePath, contentToWrite);
}

namespace
{


}





