#include "DictionaryWordsCsvFileReader.h"

#include <iostream>
#include <sstream>

#include "utils/StringHelper.h"
#include "utils/exceptions/FileNotFound.h"

namespace glossary::dictionaryRepository
{
namespace
{
constexpr auto wordSeparator{","};
constexpr auto englishWordIndex{0};
constexpr auto translationIndex{1};
}

DictionaryWordsCsvFileReader::DictionaryWordsCsvFileReader(
    std::shared_ptr<const utils::FileAccess> fileAccessInit)
    : fileAccess{std::move(fileAccessInit)}
{
}

boost::optional<DictionaryWords>
DictionaryWordsCsvFileReader::readDictionaryWords(const std::string& absolutePath) const
{
    if (not fileAccess->exists(absolutePath))
    {
        std::cerr << "File does not exist: " << absolutePath;
        return boost::none;
    }

    const auto dictionaryWordsContent = fileAccess->readContent(absolutePath);
    if (not dictionaryWordsContentIsValid(dictionaryWordsContent))
    {
        std::cerr << "Dictionary words from file :" << absolutePath << " are not properly formatted";
        return boost::none;
    }
    return getDictionaryWords(dictionaryWordsContent);
}

bool DictionaryWordsCsvFileReader::dictionaryWordsContentIsValid(
    const std::string& dictionaryWordsContent) const
{
    return validator.validate(dictionaryWordsContent) == ValidationResult::Valid;
}

DictionaryWords DictionaryWordsCsvFileReader::getDictionaryWords(const std::string& dictionaryContent) const
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

boost::optional<DictionaryWord> DictionaryWordsCsvFileReader::getDictionaryWord(const std::string& line) const
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