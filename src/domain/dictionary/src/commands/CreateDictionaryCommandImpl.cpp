#include "CreateDictionaryCommandImpl.h"

namespace glossary::dictionary
{
CreateDictionaryCommandImpl::CreateDictionaryCommandImpl(std::shared_ptr<DictionaryRepository> dictionaryRepositoryInit)
    : dictionaryRepository{std::move(dictionaryRepositoryInit)}
{
}

void CreateDictionaryCommandImpl::addDictionary(const std::string& dictionaryName)
{
    dictionaryRepository->addDictionary(dictionaryName);
}

}
