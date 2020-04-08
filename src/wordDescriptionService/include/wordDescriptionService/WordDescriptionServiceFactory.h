#pragma once

#include <memory>

#include "WordDescriptionRetrieverService.h"
#include "wordDescriptionRepository/WordDescriptionRepository.h"
#include "wordDescriptionDownloader/WordDescriptionDownloader.h"

namespace glossary::wordDescriptionService
{
class WordDescriptionServiceFactory
{
public:
    virtual ~WordDescriptionServiceFactory() = default;

    virtual std::unique_ptr<WordDescriptionRetrieverService>
    createWordDescriptionService(const std::shared_ptr<wordDescriptionDownloader::WordDescriptionDownloader>&,
                             const std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository>&) const = 0;

    static std::unique_ptr<WordDescriptionServiceFactory> createWordDescriptionServiceFactory();
};
}