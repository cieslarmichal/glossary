#include "DictionaryWordsTextFileReader.h"

#include <iostream>
#include <sstream>

#include "utils/StringHelper.h"
#include "utils/exceptions/FileNotFound.h"

namespace dictionaryRepository
{
DictionaryWordsTextFileReader::DictionaryWordsTextFileReader(
    std::shared_ptr<const utils::FileAccess> fileAccessInit)
    : fileAccess{std::move(fileAccessInit)}
{
}

DictionaryWords DictionaryWordsTextFileReader::readDictionaryWords(const std::string& absolutePath) const
{
    if (fileAccess->exists(absolutePath))
    {
        const auto dictionaryWordsContent = fileAccess->readContent(absolutePath);
        return getDictionaryWords(dictionaryWordsContent);
    }

    std::cerr << "Error while reading dictionaryWords from file: " << absolutePath;
    return {};
}

DictionaryWords DictionaryWordsTextFileReader::getDictionaryWords(const std::string& dictionaryContent) const
{
    DictionaryWords dictionaryWords{};
    for (const auto& line : utils::getSplitLines(dictionaryContent))
    {
        if (not line.empty())
        {
            if (const auto wordWithTranslation = getDictionaryWord(line))
            {
                dictionaryWords.push_back(*wordWithTranslation);
            }
        }
    }
    return dictionaryWords;
}

boost::optional<DictionaryWord>
DictionaryWordsTextFileReader::getDictionaryWord(const std::string& line) const
{
    std::stringstream lineStream{line};
    std::string englishWord;
    std::string polishWord;
    lineStream >> englishWord >> polishWord;
    if (englishWord.empty())
    {
        return boost::none;
    }
    if (polishWord.empty())
    {
        return DictionaryWord{englishWord, boost::none};
    }
    return DictionaryWord{englishWord, polishWord};
}

}