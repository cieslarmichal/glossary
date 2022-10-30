#pragma once

#include <memory>

#include "../clients/WordsApiClient.h"
#include "../repositories/WordDescriptionRepository.h"
#include "queries/GetWordDescriptionQuery.h"

namespace glossary::dictionary
{
class GetWordDescriptionQueryImpl : public GetWordDescriptionQuery
{
public:
    GetWordDescriptionQueryImpl(std::shared_ptr<WordDescriptionRepository>, std::unique_ptr<WordsApiClient>);

    WordDescription getWordDescription(const std::string& englishName) const override;

private:
    std::shared_ptr<WordDescriptionRepository> wordDescriptionRepository;
    std::unique_ptr<WordsApiClient> wordsApiClient;
};
}
