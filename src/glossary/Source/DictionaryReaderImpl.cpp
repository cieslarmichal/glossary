#include "DictionaryReaderImpl.h"

#include <iostream>
#include <sstream>

#include "utils/StringHelper.h"
#include "utils/exceptions/FileNotFound.h"

const std::string DictionaryReaderImpl::fileDirectory{"database/"};
const std::string DictionaryReaderImpl::fileName{"input.txt"};
const std::string DictionaryReaderImpl::filePath{fileDirectory + fileName};

DictionaryReaderImpl::DictionaryReaderImpl(std::shared_ptr<const utils::FileAccess> access)
    : fileAccess{std::move(access)}
{
}

Dictionaries DictionaryReaderImpl::readDictionaries() const
{
    std::string dictionaryContent;
    try
    {
        dictionaryContent = fileAccess->readContent(filePath);
    }
    catch (const utils::exceptions::FileNotFound& e)
    {
        std::cerr << "Error while reading translations from file: " << e.what();
        return {};
    }

    std::map<DictionaryName, Dictionary> dictionaries;
    dictionaries["base"] = processDictionaryContent(dictionaryContent);
    return dictionaries;
}

Dictionary DictionaryReaderImpl::processDictionaryContent(const std::string& dictionaryContent) const
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
    translationsDb::TranslatedText englishWord;
    translationsDb::SourceText polishWord;
    lineStream >> englishWord >> polishWord;
    if (!englishWord.empty() && !polishWord.empty())
    {
        return translationsDb::Translation{polishWord, englishWord};
        // TODO: add strong typedefs
    }
    return boost::none;
}
