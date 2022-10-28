#include "AddWordToDictionaryCommandImpl.h"

namespace glossary::dictionary
{
AddWordToDictionaryCommandImpl::AddWordToDictionaryCommandImpl(
    std::shared_ptr<DictionaryRepository> dictionaryRepositoryInit)
    : dictionaryRepository{std::move(dictionaryRepositoryInit)}
{
}
void AddWordToDictionaryCommandImpl::addWordToDictionary(const std::string& dictionaryName,
                                                         const DictionaryWord& dictionaryWord)
{
    dictionaryRepository->addWordToDictionary(dictionaryWord, dictionaryName);
}

}
