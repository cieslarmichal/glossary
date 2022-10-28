#pragma once

#include <memory>

#include "../repositories/DictionaryRepository.h"
#include "queries/GetDictionariesQuery.h"

namespace glossary::dictionary
{
class GetDictionariesQueryImpl : public GetDictionariesQuery
{
public:
    explicit GetDictionariesQueryImpl(std::shared_ptr<DictionaryRepository>);

    std::vector<Dictionary> getDictionaries() const override;

private:
    std::shared_ptr<DictionaryRepository> dictionaryRepository;
};
}
