#include "WordsDictionaryMembershipFinder.h"

namespace glossary::dictionaryService
{

DictionaryNames
WordsDictionaryMembershipFinder::findDictionariesContainingEnglishWord(const EnglishWord& englishWord,
                                                                       const Dictionaries& dictionaries) const
{
    DictionaryNames dictionariesContainingEnglishWord;

    for (const auto& dictionary : dictionaries)
    {
        if (englishWordExistsInDictionary(englishWord, dictionary))
        {
            dictionariesContainingEnglishWord.emplace_back(dictionary.name);
        }
    }
    return dictionariesContainingEnglishWord;
}

DictionaryNames WordsDictionaryMembershipFinder::findDictionariesContainingEnglishWordTranslation(
    const std::string& englishWordTranslation, const Dictionaries& dictionaries) const
{
    DictionaryNames dictionariesContainingEnglishWordTranslation;

    for (const auto& dictionary : dictionaries)
    {
        if (englishWordTranslationExistsInDictionary(englishWordTranslation, dictionary))
        {
            dictionariesContainingEnglishWordTranslation.emplace_back(dictionary.name);
        }
    }
    return dictionariesContainingEnglishWordTranslation;
}

bool WordsDictionaryMembershipFinder::englishWordExistsInDictionary(const EnglishWord& englishWordToFind,
                                                                    const Dictionary& dictionary) const
{
    auto englishWordExists = std::find_if(dictionary.words.begin(), dictionary.words.end(),
                                          [&englishWordToFind](const DictionaryWord& dictionaryWord) {
                                              return dictionaryWord.englishWord == englishWordToFind;
                                          });
    return englishWordExists != dictionary.words.end();
}

bool WordsDictionaryMembershipFinder::englishWordTranslationExistsInDictionary(
    const std::string& englishWordTranslation, const Dictionary& dictionary) const
{
    auto englishWordTranslationExists = std::find_if(
        dictionary.words.begin(), dictionary.words.end(),
        [&englishWordTranslation](const DictionaryWord& dictionaryWord) {
            return dictionaryWord.translation && (*dictionaryWord.translation == englishWordTranslation);
        });
    return englishWordTranslationExists != dictionary.words.end();
}

}