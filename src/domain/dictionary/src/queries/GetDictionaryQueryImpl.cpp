#include "GetDictionaryQueryImpl.h"

namespace glossary::dictionary
{
GetDictionaryQueryImpl::GetDictionaryQueryImpl(std::shared_ptr<DictionaryRepository> dictionaryRepositoryInit)
    : dictionaryRepository{std::move(dictionaryRepositoryInit)}
{
}

std::optional<Dictionary> GetDictionaryQueryImpl::getDictionary(const std::string& dictionaryName) const
{
    return dictionaryRepository->getDictionary(dictionaryName);
}

}
