#include "DictionaryWordsCsvFileContentValidator.h"

#include "utils/StringHelper.h"

namespace dictionaryRepository
{

namespace
{
constexpr auto wordSeparator{","};
constexpr auto englishWordIndex{0};
constexpr auto requiredAmountOfWordsInLine{2};
}

ValidationResult DictionaryWordsCsvFileContentValidator::validate(const std::string& content) const
{
    if (dictionaryWordsContentIsValid(content))
        return ValidationResult::Valid;
    return ValidationResult::Invalid;
}

bool DictionaryWordsCsvFileContentValidator::dictionaryWordsContentIsValid(
    const std::string& dictionaryWordsContent) const
{
    for (const auto& line : utils::split(dictionaryWordsContent))
    {
        if (not dictionaryWordLineIsValid(line))
            return false;
    }
    return true;
}
bool DictionaryWordsCsvFileContentValidator::dictionaryWordLineIsValid(
    const std::string& dictionaryWordLine) const
{
    if (dictionaryWordLine.empty())
        return true;

    auto separatedWords = utils::split(dictionaryWordLine, wordSeparator);
    utils::trim(separatedWords);

    auto lineContainsBothRequiredWords = separatedWords.size() == requiredAmountOfWordsInLine;
    auto englishWordIsNotEmpty = not separatedWords.at(englishWordIndex).empty();
    return lineContainsBothRequiredWords && englishWordIsNotEmpty;
}

}
