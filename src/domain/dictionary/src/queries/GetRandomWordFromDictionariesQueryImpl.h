#pragma once

#include <memory>

#include "../repositories/DictionaryRepository.h"
#include "queries/GetRandomWordFromDictionariesQuery.h"
#include "random/RandomNumberGenerator.h"

namespace glossary::dictionary
{
class GetRandomWordFromDictionariesQueryImpl : public GetRandomWordFromDictionariesQuery
{
public:
    GetRandomWordFromDictionariesQueryImpl(std::shared_ptr<DictionaryRepository>,
                                           std::shared_ptr<common::random::RandomNumberGenerator>);

    DictionaryWord getRandomWord() const override;

private:
    std::shared_ptr<DictionaryRepository> dictionaryRepository;
    std::shared_ptr<common::random::RandomNumberGenerator> randomNumberGenerator;
};
}
