#include "DictionaryReader.h"

#include "StringHelper.h"
#include <sstream>


namespace
{
const std::string wordTranslationsFilePath{"../database/dictionary.txt"};
}


DictionaryReader::DictionaryReader(FileAccess & access) :fileAccess{access}
{
}

std::vector<WordWithTranslation> DictionaryReader::read() const
{
    auto dictionaryContent = fileAccess.readContent(wordTranslationsFilePath);
    return processDictionaryContent(dictionaryContent);
}

std::vector<WordWithTranslation> DictionaryReader::processDictionaryContent(const std::string& dictionaryContent) const
{
    std::vector<WordWithTranslation> wordsWithTranslation;
    for (const auto &line : stringHelper::getSplitLines(dictionaryContent))
    {
        wordsWithTranslation.push_back(getWordWithTranslation(line));
    }
    return wordsWithTranslation;
}

WordWithTranslation DictionaryReader::getWordWithTranslation(const std::string & line) const
{
    std::stringstream lineStream{line};
    EnglishWord englishWord;
    PolishWord polishWord;
    lineStream >> englishWord >> polishWord;
    return WordWithTranslation{englishWord, polishWord};
}
