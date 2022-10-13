#pragma once

#include <memory>

#include "../../../common/fileSystem/include/FileAccess.h"
#include "WordDescriptionRepository.h"
#include "WordDescriptionRepositoryApi.h"

namespace glossary::wordDescriptionRepository
{
class WORD_DESCRIPTION_REPOSITORY_API WordDescriptionRepositoryFactory
{
public:
    virtual ~WordDescriptionRepositoryFactory() = default;

    virtual std::unique_ptr<WordDescriptionRepository> createWordDescriptionRepository() const = 0;

    static std::unique_ptr<WordDescriptionRepositoryFactory>
    createWordDescriptionRepositoryFactory(const std::shared_ptr<const common::FileAccess>&);
};
}