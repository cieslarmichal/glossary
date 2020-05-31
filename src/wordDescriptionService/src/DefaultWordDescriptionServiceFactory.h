#pragma once

#include "WordDescriptionServiceFactory.h"
#include "utils/FileAccess.h"

namespace glossary::wordDescriptionService
{
class DefaultWordDescriptionServiceFactory : public WordDescriptionServiceFactory
{
public:
    explicit DefaultWordDescriptionServiceFactory(std::shared_ptr<const utils::FileAccess>);

    std::unique_ptr<WordDescriptionService> createWordDescriptionService(
        const std::shared_ptr<wordDescriptionDownloader::WordDescriptionDownloader>&,
        const std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository>&) const override;

private:
    std::shared_ptr<const utils::FileAccess> fileAccess;
};
}