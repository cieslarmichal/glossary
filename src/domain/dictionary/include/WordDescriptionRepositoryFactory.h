#pragma once

#include <memory>

#include "FileAccess.h"
#include "WordDescriptionRepository.h"

namespace glossary::dictionary
{
class WordDescriptionRepositoryFactory
{
public:
    virtual ~WordDescriptionRepositoryFactory() = default;

    virtual std::unique_ptr<WordDescriptionRepository> createWordDescriptionRepository() const = 0;

    static std::unique_ptr<WordDescriptionRepositoryFactory>
    createWordDescriptionRepositoryFactory(const std::shared_ptr<const common::fileSystem::FileAccess>&);
};
}