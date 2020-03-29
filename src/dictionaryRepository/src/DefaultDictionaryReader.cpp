#include "DefaultDictionaryReader.h"

#include <iostream>
#include <sstream>

#include "utils/StringHelper.h"
#include "utils/exceptions/FileNotFound.h"

namespace dictionaryRepository
{

const std::string DefaultDictionaryReader::directory{"database/dictionaries/"};
const std::string DefaultDictionaryReader::filename{directory + "input.txt"};

DefaultDictionaryReader::DefaultDictionaryReader(std::shared_ptr<const utils::FileAccess> access)
    : fileAccess{std::move(access)}
{
}

Dictionaries DefaultDictionaryReader::readDictionaries() const
{
    std::string dictionaryContent;
    try
    {
        dictionaryContent = fileAccess->readContent(filename);
    }
    catch (const utils::exceptions::FileNotFound& e)
    {
        std::cerr << "Error while reading translations from file: " << e.what();
        return {};
    }

    Dictionaries dictionaries;
    dictionaries.emplace_back(getDictionary(dictionaryContent));
    return dictionaries;
}

Dictionary DefaultDictionaryReader::getDictionary(const std::string& dictionaryContent) const
{
    Dictionary dictionary{"dictionary", {}};
    for (const auto& line : utils::getSplitLines(dictionaryContent))
    {
        if (not line.empty())
        {
            if (const auto wordWithTranslation = getDictionaryWord(line))
            {
                dictionary.words.push_back(*wordWithTranslation);
            }
        }
    }
    return dictionary;
}

boost::optional<DictionaryWord> DefaultDictionaryReader::getDictionaryWord(const std::string& line) const
{
    std::stringstream lineStream{line};
    std::string englishWord;
    std::string polishWord;
    lineStream >> englishWord >> polishWord;
    if(englishWord.empty())
    {
        return boost::none;
    }
    if(not polishWord.empty())
    {
        return DictionaryWord{englishWord, polishWord};
    }
    else
    {
        return DictionaryWord{englishWord, boost::none};
    }
}
}