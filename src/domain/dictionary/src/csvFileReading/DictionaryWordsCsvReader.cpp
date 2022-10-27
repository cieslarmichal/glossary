#include "DictionaryWordsCsvReader.h"

#include <algorithm>

#include "collection/StringHelper.h"
#include "exceptions/InvalidDictionaryWordsCsvFile.h"

namespace glossary::dictionary
{
namespace
{
constexpr auto wordSeparator{","};
constexpr auto englishWordIndex{0};
constexpr auto translationIndex{1};
constexpr auto requiredAmountOfWordsInLine{2};
}

DictionaryWordsCsvReader::DictionaryWordsCsvReader(std::shared_ptr<const common::fileSystem::FileAccess> fileAccessInit)
    : fileAccess{std::move(fileAccessInit)}
{
}

std::vector<DictionaryWord> DictionaryWordsCsvReader::readDictionaryWords(const std::string& absolutePath) const
{
    const auto csvDictionaryWords = fileAccess->readContent(absolutePath);

    if (not dictionaryWordsCsvIsValid(csvDictionaryWords))
    {
        throw exceptions::InvalidDictionaryWordsCsvFile("");
    }

    std::vector<DictionaryWord> dictionaryWords;

    const auto csvLines = common::collection::split(csvDictionaryWords);

    const auto csvNonEmptyLines = common::collection::getNonEmptyLines(csvLines);

    for (const auto& line : csvNonEmptyLines)
    {
        auto separatedWords = common::collection::split(line, wordSeparator);

        common::collection::trim(separatedWords);

        const auto englishWord = separatedWords.at(englishWordIndex);

        const auto translationValue = separatedWords.at(translationIndex);

        const auto translation = translationValue.empty() ? std::optional<std::string>{std::nullopt} : translationValue;

        const auto dictionaryWord = DictionaryWord{englishWord, translation};

        dictionaryWords.push_back(dictionaryWord);
    }

    return dictionaryWords;
}

bool DictionaryWordsCsvReader::dictionaryWordsCsvIsValid(const std::string& csvDictionaryWords) const
{
    const auto cvsLines = common::collection::split(csvDictionaryWords);

    const auto csvLinesAreValid =
        std::ranges::all_of(cvsLines.cbegin(), cvsLines.cend(),
                            [this](const std::string& csvLine) { return dictionaryWordCsvLineIsValid(csvLine); });

    return csvLinesAreValid;
}

bool DictionaryWordsCsvReader::dictionaryWordCsvLineIsValid(const std::string& csvDictionaryWordLine) const
{
    if (csvDictionaryWordLine.empty())
    {
        return true;
    }

    auto separatedWords = common::collection::split(csvDictionaryWordLine, wordSeparator);

    common::collection::trim(separatedWords);

    const auto lineContainsBothRequiredWords = separatedWords.size() == requiredAmountOfWordsInLine;

    if (!lineContainsBothRequiredWords)
    {
        return false;
    }

    auto englishWordIsMissing = separatedWords.at(englishWordIndex).empty();

    if (englishWordIsMissing)
    {
        return false;
    }

    return true;
}

}
