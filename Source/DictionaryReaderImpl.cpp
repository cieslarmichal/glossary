#include "DictionaryReaderImpl.h"

#include "StringHelper.h"
#include <sstream>


namespace
{
const std::string dictionaryFilePath{"../database/dictionary.txt"};
}


DictionaryReaderImpl::DictionaryReaderImpl(FileAccess & access) : fileAccess{access}
{
}

std::vector<WordWithTranslation> DictionaryReaderImpl::read() const
{
    auto dictionaryContent = fileAccess.readContent(dictionaryFilePath);
    return processDictionaryContent(dictionaryContent);
}

std::vector<WordWithTranslation> DictionaryReaderImpl::processDictionaryContent(const std::string& dictionaryContent) const
{
    std::vector<WordWithTranslation> wordsWithTranslation;
    for (const auto &line : stringHelper::getSplitLines(dictionaryContent))
    {
        if(not line.empty())
        {
            wordsWithTranslation.push_back(getWordWithTranslation(line));
        }
    }
    return wordsWithTranslation;
}

WordWithTranslation DictionaryReaderImpl::getWordWithTranslation(const std::string & line) const
{
    std::stringstream lineStream{line};
    EnglishWord englishWord;
    PolishWord polishWord;
    lineStream >> englishWord >> polishWord;
    return WordWithTranslation{englishWord, polishWord};
}
