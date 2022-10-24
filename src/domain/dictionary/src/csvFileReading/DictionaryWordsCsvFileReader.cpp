#include "DictionaryWordsCsvFileReader.h"

#include <iostream>

#include "collection/StringHelper.h"

namespace glossary::dictionary::csvFileReading
{
namespace
{
constexpr auto wordSeparator{","};
constexpr auto englishWordIndex{0};
constexpr auto translationIndex{1};
}

DictionaryWordsCsvFileReader::DictionaryWordsCsvFileReader(
    std::shared_ptr<const common::fileSystem::FileAccess> fileAccessInit)
    : fileAccess{std::move(fileAccessInit)}
{
}

std::optional<std::vector<DictionaryWord>>
DictionaryWordsCsvFileReader::readDictionaryWords(const std::string& absolutePath) const
{
    if (not fileAccess->exists(absolutePath))
    {
        std::cerr << "File does not exist: " << absolutePath;
        return std::nullopt;
    }

    const auto dictionaryWordsContent = fileAccess->readContent(absolutePath);
    if (not dictionaryWordsContentIsValid(dictionaryWordsContent))
    {
        std::cerr << "Dictionary words from file :" << absolutePath << " are not properly formatted";
        return std::nullopt;
    }
    return getDictionaryWords(dictionaryWordsContent);
}

bool DictionaryWordsCsvFileReader::dictionaryWordsContentIsValid(
    const std::string& dictionaryWordsContent) const
{
    return validator.validate(dictionaryWordsContent) == ValidationResult::Valid;
}

std::vector<DictionaryWord>
DictionaryWordsCsvFileReader::getDictionaryWords(const std::string& dictionaryContent) const
{
    std::vector<DictionaryWord> dictionaryWords{};
    for (const auto& line : common::collection::split(dictionaryContent))
    {
        if (const auto wordWithTranslation = getDictionaryWord(line))
        {
            dictionaryWords.push_back(*wordWithTranslation);
        }
    }
    return dictionaryWords;
}

std::optional<DictionaryWord> DictionaryWordsCsvFileReader::getDictionaryWord(const std::string& line) const
{
    if (line.empty())
        return std::nullopt;

    auto separatedWords = common::collection::split(line, wordSeparator);
    common::collection::trim(separatedWords);
    std::string englishWord = separatedWords.at(englishWordIndex);
    std::string polishTranslation = separatedWords.at(translationIndex);

    if (polishTranslation.empty())
        return DictionaryWord{englishWord, std::nullopt};

    return DictionaryWord{englishWord, polishTranslation};
}

}