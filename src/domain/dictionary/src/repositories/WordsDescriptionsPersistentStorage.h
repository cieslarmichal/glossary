#pragma once

#include <memory>

#include "../serializers/WordsDescriptionsSerializer.h"
#include "fileSystem/FileAccess.h"
#include "WordsDescriptionsMemoryStorage.h"
#include "WordsDescriptionsStorage.h"

namespace glossary::dictionary
{
class WordsDescriptionsPersistentStorage : public WordsDescriptionsStorage
{
public:
    WordsDescriptionsPersistentStorage(std::shared_ptr<const common::fileSystem::FileAccess>,
                                       std::shared_ptr<const WordsDescriptionsSerializer>);

    void addWordDescription(const WordDescription&) override;
    std::optional<WordDescription> getWordDescription(const std::string&) const override;
    std::vector<WordDescription> getWordsDescriptions() const override;
    bool contains(const std::string&) const override;
    std::vector<WordDescription>::size_type size() const override;
    bool empty() const override;

private:
    void loadFile();
    void serialize() const;

    std::shared_ptr<const common::fileSystem::FileAccess> fileAccess;
    std::shared_ptr<const WordsDescriptionsSerializer> serializer;
    WordsDescriptionsMemoryStorage storage;

    static const std::string directory;
    static const std::string filename;
};
}
