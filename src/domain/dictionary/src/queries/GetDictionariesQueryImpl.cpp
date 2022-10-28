#include "GetDictionariesQueryImpl.h"

namespace glossary::dictionary
{
GetDictionariesQueryImpl::GetDictionariesQueryImpl(std::shared_ptr<DictionaryRepository> dictionaryRepositoryInit)
    : dictionaryRepository{std::move(dictionaryRepositoryInit)}
{
}

std::vector<Dictionary> GetDictionariesQueryImpl::getDictionaries() const
{
    return dictionaryRepository->getDictionaries();
}

}
