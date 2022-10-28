#pragma once

#include <memory>

#include "../repositories/DictionaryRepository.h"
#include "queries/GetDictionariesNamesQuery.h"

namespace glossary::dictionary
{
class GetDictionariesNamesQueryImpl : public GetDictionariesNamesQuery
{
public:
    explicit GetDictionariesNamesQueryImpl(std::shared_ptr<DictionaryRepository>);

    std::vector<std::string> getDictionariesNames() const override;

private:
    std::shared_ptr<DictionaryRepository> dictionaryRepository;
};
}
