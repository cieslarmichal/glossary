#pragma once

#include <memory>

#include "../repositories/DictionaryRepository.h"
#include "queries/GetDictionaryEnglishWordsQuery.h"

namespace glossary::dictionary
{
class GetDictionaryEnglishWordsQueryImpl : public GetDictionaryEnglishWordsQuery
{
public:
    explicit GetDictionaryEnglishWordsQueryImpl(std::shared_ptr<DictionaryRepository>);

    std::vector<std::string> getDictionaryEnglishWords(const std::string& dictionaryName) const override;

private:
    std::shared_ptr<DictionaryRepository> dictionaryRepository;
};
}
