#include "DictionaryReaderImpl.h"

#include "StringHelper.h"
#include <sstream>
#include <iostream>
#include "Exceptions/FileNotFound.h"

const std::string DictionaryReaderImpl::fileDirectory{"../database"};
const std::string DictionaryReaderImpl::fileName{"/dictionary.txt"};
const std::string DictionaryReaderImpl::filePath{fileDirectory + fileName};

DictionaryReaderImpl::DictionaryReaderImpl(std::shared_ptr<const FileAccess> access) : fileAccess{access}
{
}

std::vector<WordWithTranslation> DictionaryReaderImpl::read() const
{
    std::string dictionaryContent;
    try
    {
        dictionaryContent = fileAccess->readContent(filePath);

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
            if (const auto wordWithTranslation = getWordWithTranslation(line))
            {
                wordsWithTranslation.push_back(*wordWithTranslation);
            }
        }
    }
    return wordsWithTranslation;
}

boost::optional<WordWithTranslation> DictionaryReaderImpl::getWordWithTranslation(const std::string& line) const
{
    std::stringstream lineStream{line};
    EnglishWord englishWord;
    PolishWord polishWord;
    lineStream >> englishWord >> polishWord;
    if (!englishWord.empty() && !polishWord.empty())
    {
        return WordWithTranslation{englishWord, polishWord};
    }
    return boost::none;
}
