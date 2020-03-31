#include "DictionaryWordsCSVFileReader.h"

#include <iostream>
#include <sstream>

#include "utils/StringHelper.h"
#include "utils/exceptions/FileNotFound.h"

namespace dictionaryRepository
{
namespace
{
constexpr auto wordSeparator{","};
constexpr auto englishWordIndex{0};
constexpr auto translationIndex{1};
constexpr auto requiredAmountOfWordsInLine{2};
}

DictionaryWordsCSVFileReader::DictionaryWordsCSVFileReader(
    std::shared_ptr<const utils::FileAccess> fileAccessInit)
    : fileAccess{std::move(fileAccessInit)}
{
}

DictionaryWords DictionaryWordsCSVFileReader::readDictionaryWords(const std::string& absolutePath) const
{
    if (not fileAccess->exists(absolutePath))
        std::cerr << "File does not exist: " << absolutePath;

    const auto dictionaryWordsContent = fileAccess->readContent(absolutePath);
    if (dictionaryWordsContentIsValid(dictionaryWordsContent))
        return getDictionaryWords(dictionaryWordsContent);

    std::cerr << "Dictionary words from file :" << absolutePath << " are not properly formatted";
    return {};
}

bool DictionaryWordsCSVFileReader::dictionaryWordsContentIsValid(
    const std::string& dictionaryWordsContent) const
{
    for (const auto& line : utils::split(dictionaryWordsContent))
    {
        if (not dictionaryWordLineIsValid(line))
            return false;
    }
    return true;
}

bool DictionaryWordsCSVFileReader::dictionaryWordLineIsValid(const std::string& dictionaryWordLine) const
{
    if (dictionaryWordLine.empty())
    {
        return true;
    }
    auto separatedWords = utils::split(dictionaryWordLine, wordSeparator);
    utils::trim(separatedWords);
    return not(separatedWords.size() < requiredAmountOfWordsInLine ||
               separatedWords.at(englishWordIndex).empty());
}

DictionaryWords DictionaryWordsCSVFileReader::getDictionaryWords(const std::string& dictionaryContent) const
{
    DictionaryWords dictionaryWords{};
    for (const auto& line : utils::split(dictionaryContent))
    {
        if (const auto wordWithTranslation = getDictionaryWord(line))
        {
            dictionaryWords.push_back(*wordWithTranslation);
        }
    }
    return dictionaryWords;
}

boost::optional<DictionaryWord> DictionaryWordsCSVFileReader::getDictionaryWord(const std::string& line) const
{
    if (line.empty())
        return boost::none;

    auto separatedWords = utils::split(line, wordSeparator);
    utils::trim(separatedWords);
    std::string englishWord = separatedWords.at(englishWordIndex);
    std::string polishTranslation = separatedWords.at(translationIndex);

    if (polishTranslation.empty())
        return DictionaryWord{englishWord, boost::none};

    return DictionaryWord{englishWord, polishTranslation};
}

}