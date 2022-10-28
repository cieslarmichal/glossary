#pragma once

#include <memory>

#include "../repositories/DictionaryRepository.h"
#include "queries/GetRandomWordFromDictionaryQuery.h"
#include "random/RandomNumberGenerator.h"

namespace glossary::dictionary
{
class GetRandomWordFromDictionaryQueryImpl : public GetRandomWordFromDictionaryQuery
{
public:
    explicit GetRandomWordFromDictionaryQueryImpl(std::shared_ptr<DictionaryRepository>,
                                                  std::shared_ptr<common::random::RandomNumberGenerator>);

    DictionaryWord getRandomWord(const std::string& dictionaryName) const override;

private:
    std::shared_ptr<DictionaryRepository> dictionaryRepository;
    std::shared_ptr<common::random::RandomNumberGenerator> randomNumberGenerator;
};
}
