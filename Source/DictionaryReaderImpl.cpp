#include "DictionaryReaderImpl.h"

#include <iostream>
#include <sstream>

#include "StringHelper.h"
#include "exceptions/FileNotFound.h"

const std::string DictionaryReaderImpl::fileDirectory{"../database"};
const std::string DictionaryReaderImpl::fileName{"/dictionary.txt"};
const std::string DictionaryReaderImpl::filePath{fileDirectory + fileName};

DictionaryReaderImpl::DictionaryReaderImpl(
    std::shared_ptr<const FileAccess> access)
    : fileAccess{access}
{
}

std::vector<Translation> DictionaryReaderImpl::read() const
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

std::vector<Translation> DictionaryReaderImpl::processDictionaryContent(
    const std::string& dictionaryContent) const
{
    std::vector<Translation> wordsWithTranslation;
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

boost::optional<Translation>
DictionaryReaderImpl::getWordWithTranslation(const std::string& line) const
{
    std::stringstream lineStream{line};
    EnglishWord englishWord;
    PolishWord polishWord;
    lineStream >> englishWord >> polishWord;
    if (!englishWord.empty() && !polishWord.empty())
    {
        return Translation{polishWord, englishWord};
        // TODO: add strong typedefs
    }
    return boost::none;
}
