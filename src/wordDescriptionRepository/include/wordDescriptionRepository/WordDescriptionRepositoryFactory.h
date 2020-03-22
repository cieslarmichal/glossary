#pragma once

#include <memory>

#include "WordDescriptionRepository.h"
#include "utils/FileAccess.h"

namespace wordDescriptionRepository
{
class WordDescriptionRepositoryFactory
{
public:
    virtual ~WordDescriptionRepositoryFactory() = default;

    virtual std::unique_ptr<WordDescriptionRepository> createWordsDescriptionDb() const = 0;

    static std::unique_ptr<WordDescriptionRepositoryFactory>
    createWordsDescriptionsDbFactory(const std::shared_ptr<const utils::FileAccess>&);
};
}