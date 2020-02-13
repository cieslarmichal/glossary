#include "DictionaryReaderImpl.h"

#include <iostream>
#include <sstream>

#include "exceptions/FileNotFound.h"
#include "utils/StringHelper.h"

const std::string DictionaryReaderImpl::fileDirectory{"../database"};
const std::string DictionaryReaderImpl::fileName{"/translations.txt"};
const std::string DictionaryReaderImpl::filePath{fileDirectory + fileName};

DictionaryReaderImpl::DictionaryReaderImpl(
    std::shared_ptr<const utils::FileAccess> access)
    : fileAccess{access}
{
}

std::vector<translationsDb::Translation> DictionaryReaderImpl::read() const
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

std::vector<translationsDb::Translation> DictionaryReaderImpl::processDictionaryContent(
    const std::string& dictionaryContent) const
{
    std::vector<translationsDb::Translation> wordsWithTranslation;
    for (const auto& line : utils::getSplitLines(dictionaryContent))
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

boost::optional<translationsDb::Translation>
DictionaryReaderImpl::getWordWithTranslation(const std::string& line) const
{
    std::stringstream lineStream{line};
    EnglishWord englishWord;
    PolishWord polishWord;
    lineStream >> englishWord >> polishWord;
    if (!englishWord.empty() && !polishWord.empty())
    {
        return translationsDb::Translation{polishWord, englishWord};
        // TODO: add strong typedefs
    }
    return boost::none;
}
