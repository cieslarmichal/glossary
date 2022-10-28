#include "RemoveWordFromDictionaryCommandImpl.h"

namespace glossary::dictionary
{
RemoveWordFromDictionaryCommandImpl::RemoveWordFromDictionaryCommandImpl(
    std::shared_ptr<DictionaryRepository> dictionaryRepositoryInit)
    : dictionaryRepository{std::move(dictionaryRepositoryInit)}
{
}
void RemoveWordFromDictionaryCommandImpl::removeWordFromDictionary(const std::string& dictionaryName,
                                                                   const std::string& englishWord)
{
    dictionaryRepository->removeWordFromDictionary(englishWord, dictionaryName);
}

}
