#include "GetDictionaryEnglishWordsQueryImpl.h"

#include "exceptions/DictionaryNotFoundError.h"

namespace glossary::dictionary
{
GetDictionaryEnglishWordsQueryImpl::GetDictionaryEnglishWordsQueryImpl(
    std::shared_ptr<DictionaryRepository> dictionaryRepositoryInit)
    : dictionaryRepository{std::move(dictionaryRepositoryInit)}
{
}
std::vector<std::string>
GetDictionaryEnglishWordsQueryImpl::getDictionaryEnglishWords(const std::string& dictionaryName) const
{
    const auto dictionary = dictionaryRepository->getDictionary(dictionaryName);

    if (!dictionary)
    {
        throw exceptions::DictionaryNotFoundError{""};
    }

    std::vector<std::string> englishWords;

    for (const auto& dictionaryWord : dictionary->words)
    {
        englishWords.emplace_back(dictionaryWord.englishWord);
    }

    return englishWords;
}

}
