#pragma once

#include <memory>

#include "../repositories/DictionaryRepository.h"
#include "queries/GetDictionaryQuery.h"

namespace glossary::dictionary
{
class GetDictionaryQueryImpl : public GetDictionaryQuery
{
public:
    explicit GetDictionaryQueryImpl(std::shared_ptr<DictionaryRepository>);

    std::optional<Dictionary> getDictionary(const std::string& dictionaryName) const override;

private:
    std::shared_ptr<DictionaryRepository> dictionaryRepository;
};
}
