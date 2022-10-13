#pragma once

#include <memory>

#include "../../../common/fileSystem/include/FileAccess.h"
#include "WordDescriptionService.h"
#include "WordDescriptionServiceApi.h"
#include "wordDescriptionDownloader/WordDescriptionDownloader.h"
#include "wordDescriptionRepository/WordDescriptionRepository.h"

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
    createWordDescriptionServiceFactory(const std::shared_ptr<const common::FileAccess>&);
};
}