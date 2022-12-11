#include "RemoveDictionaryCommandImpl.h"

namespace glossary::dictionary
{
RemoveDictionaryCommandImpl::RemoveDictionaryCommandImpl(std::shared_ptr<DictionaryRepository> dictionaryRepositoryInit)
    : dictionaryRepository{std::move(dictionaryRepositoryInit)}
{
}

void RemoveDictionaryCommandImpl::removeDictionary(const std::string& dictionaryName)
{
    dictionaryRepository->removeDictionary(dictionaryName);
}

}
