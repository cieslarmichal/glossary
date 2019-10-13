#include "DictionaryReaderImpl.h"

#include "StringHelper.h"
#include <sstream>
#include <iostream>
#include "Exceptions/FileNotFound.h"

const std::string DictionaryReaderImpl::dictionaryFilePath{"../database/dictionary.txt"};

DictionaryReaderImpl::DictionaryReaderImpl(std::shared_ptr<const FileAccess> access) : fileAccess{access}
{
}

std::vector<WordWithTranslation> DictionaryReaderImpl::read() const
{
    std::string dictionaryContent;
    try
    {
        dictionaryContent = fileAccess->readContent(dictionaryFilePath);

    }
    catch (const exceptions::FileNotFound& e)
    {
        std::cerr << e.what();
        return {};
    }

    return processDictionaryContent(dictionaryContent);
}

std::vector<WordWithTranslation>
DictionaryReaderImpl::processDictionaryContent(const std::string& dictionaryContent) const
{
    std::vector<WordWithTranslation> wordsWithTranslation;
    for (const auto& line : stringHelper::getSplitLines(dictionaryContent))
    {
        if (not line.empty())
        {
            wordsWithTranslation.push_back(getWordWithTranslation(line));
        }
    }
    return wordsWithTranslation;
}

WordWithTranslation DictionaryReaderImpl::getWordWithTranslation(const std::string& line) const
{
    std::stringstream lineStream{line};
    EnglishWord englishWord;
    PolishWord polishWord;
    lineStream >> englishWord >> polishWord;
    return WordWithTranslation{englishWord, polishWord};
}
