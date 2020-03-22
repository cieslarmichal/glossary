#include "DefaultDictionaryReader.h"

#include <iostream>
#include <sstream>

#include "utils/StringHelper.h"
#include "utils/exceptions/FileNotFound.h"

const std::string DefaultDictionaryReader::directory{"database/dictionaries/"};
const std::string DefaultDictionaryReader::filename{directory+"input.txt"};

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

    std::map<DictionaryName, Dictionary> dictionaries;
    dictionaries["base"] = processDictionaryContent(dictionaryContent);
    return dictionaries;
}

Dictionary DefaultDictionaryReader::processDictionaryContent(const std::string& dictionaryContent) const
{
    std::vector<translationRepository::Translation> wordsWithTranslation;
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

boost::optional<translationRepository::Translation>
DefaultDictionaryReader::getWordWithTranslation(const std::string& line) const
{
    std::stringstream lineStream{line};
    translationRepository::TranslatedText englishWord;
    translationRepository::SourceText polishWord;
    lineStream >> englishWord >> polishWord;
    if (!englishWord.empty() && !polishWord.empty())
    {
        return translationRepository::Translation{polishWord, englishWord};
        // TODO: add strong typedefs
    }
    return boost::none;
}
