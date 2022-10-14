#include "WordsDictionaryMembershipFinder.h"

namespace glossary::dictionary
{

std::vector<std::string> WordsDictionaryMembershipFinder::findDictionariesContainingEnglishWord(
    const std::string& englishWord, const std::vector<Dictionary>& dictionaries) const
{
    std::vector<std::string> dictionariesContainingEnglishWord;

    for (const auto& dictionary : dictionaries)
    {
        if (englishWordExistsInDictionary(englishWord, dictionary))
        {
            dictionariesContainingEnglishWord.emplace_back(dictionary.name);
        }
    }
    return dictionariesContainingEnglishWord;
}

std::vector<std::string> WordsDictionaryMembershipFinder::findDictionariesContainingEnglishWordTranslation(
    const std::string& englishWordTranslation, const std::vector<Dictionary>& dictionaries) const
{
    std::vector<std::string> dictionariesContainingEnglishWordTranslation;

    for (const auto& dictionary : dictionaries)
    {
        if (englishWordTranslationExistsInDictionary(englishWordTranslation, dictionary))
        {
            dictionariesContainingEnglishWordTranslation.emplace_back(dictionary.name);
        }
    }
    return dictionariesContainingEnglishWordTranslation;
}

bool WordsDictionaryMembershipFinder::englishWordExistsInDictionary(const std::string& englishWordToFind,
                                                                    const Dictionary& dictionary) const
{
    auto englishWordExists = std::find_if(dictionary.words.begin(), dictionary.words.end(),
                                          [&englishWordToFind](const DictionaryWord& dictionaryWord)
                                          { return dictionaryWord.englishWord == englishWordToFind; });
    return englishWordExists != dictionary.words.end();
}

bool WordsDictionaryMembershipFinder::englishWordTranslationExistsInDictionary(
    const std::string& englishWordTranslation, const Dictionary& dictionary) const
{
    auto englishWordTranslationExists = std::find_if(
        dictionary.words.begin(), dictionary.words.end(),
        [&englishWordTranslation](const DictionaryWord& dictionaryWord)
        { return dictionaryWord.translation && (*dictionaryWord.translation == englishWordTranslation); });
    return englishWordTranslationExists != dictionary.words.end();
}

}