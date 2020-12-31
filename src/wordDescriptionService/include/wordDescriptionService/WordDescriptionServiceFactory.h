#pragma once

#include <memory>

#include "WordDescriptionService.h"
#include "utils/FileAccess.h"
#include "wordDescriptionDownloader/WordDescriptionDownloader.h"
#include "wordDescriptionRepository/WordDescriptionRepository.h"
#include "WordDescriptionServiceApi.h"

namespace glossary::wordDescriptionService
{
class WORD_DESCRIPTION_SERVICE_API WordDescriptionServiceFactory
{
public:
    virtual ~WordDescriptionServiceFactory() = default;

    virtual std::unique_ptr<WordDescriptionService> createWordDescriptionService(
        const std::shared_ptr<wordDescriptionDownloader::WordDescriptionDownloader>&,
        const std::shared_ptr<wordDescriptionRepository::WordDescriptionRepository>&) const = 0;

    static std::unique_ptr<WordDescriptionServiceFactory>
    createWordDescriptionServiceFactory(const std::shared_ptr<const utils::FileAccess>&);
};
}