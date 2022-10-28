#include "GetDictionariesEnglishWordsQueryImpl.h"

#include "exceptions/DictionaryNotFoundError.h"

namespace glossary::dictionary
{
GetDictionariesEnglishWordsQueryImpl::GetDictionariesEnglishWordsQueryImpl(
    std::shared_ptr<DictionaryRepository> dictionaryRepositoryInit)
    : dictionaryRepository{std::move(dictionaryRepositoryInit)}
{
}
std::vector<std::string> GetDictionariesEnglishWordsQueryImpl::getDictionariesEnglishWords() const
{
    const auto dictionaries = dictionaryRepository->getDictionaries();

    std::vector<std::string> allDictionaryEnglishWords;

    for (const auto& dictionary : dictionaries)
    {
        std::vector<std::string> dictionaryEnglishWords;

        for (const auto& dictionaryWord : dictionary.words)
        {
            dictionaryEnglishWords.emplace_back(dictionaryWord.englishWord);
        }

        allDictionaryEnglishWords.insert(allDictionaryEnglishWords.end(), dictionaryEnglishWords.begin(),
                                         dictionaryEnglishWords.end());
    }

    return allDictionaryEnglishWords;
}

}
