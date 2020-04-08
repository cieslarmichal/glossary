#pragma once
#include "WordDescriptionServiceFactory.h"

namespace glossary::wordDescriptionService
{
class DefaultWordDescriptionServiceFactory : public WordDescriptionServiceFactory
{
public:
    std::unique_ptr<WordDescriptionRetrieverService> createWordDescriptionService(
        const std::shared_ptr<wordDescriptionDownloader::WordDescriptionDownloader>&,
        const std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository>&) const override;
};
}