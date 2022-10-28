#pragma once

#include <memory>

#include "../repositories/DictionaryRepository.h"
#include "queries/GetDictionariesEnglishWordsQuery.h"

namespace glossary::dictionary
{
class GetDictionariesEnglishWordsQueryImpl : public GetDictionariesEnglishWordsQuery
{
public:
    explicit GetDictionariesEnglishWordsQueryImpl(std::shared_ptr<DictionaryRepository>);

    std::vector<std::string> getDictionariesEnglishWords() const override;

private:
    std::shared_ptr<DictionaryRepository> dictionaryRepository;
};
}
