#pragma once

#include <memory>

#include "../../common/fileSystem/include/FileAccess.h"
#include "WordsDescriptionsMemoryStorage.h"
#include "WordsDescriptionsSerializer.h"
#include "WordsDescriptionsStorage.h"

namespace glossary::wordDescriptionRepository
{
class WordsDescriptionsPersistentStorage : public WordsDescriptionsStorage
{
public:
    WordsDescriptionsPersistentStorage(std::shared_ptr<const common::FileAccess>,
                                       std::shared_ptr<const WordsDescriptionsSerializer>);

    void addWordDescription(const WordDescription&) override;
    boost::optional<WordDescription> getWordDescription(const std::string&) const override;
    WordsDescriptions getWordsDescriptions() const override;
    bool contains(const std::string&) const override;
    WordsDescriptions::size_type size() const override;
    bool empty() const override;

private:
    void loadFile();
    void serialize() const;

    std::shared_ptr<const common::FileAccess> fileAccess;
    std::shared_ptr<const WordsDescriptionsSerializer> serializer;
    WordsDescriptionsMemoryStorage storage;

    static const std::string directory;
    static const std::string filename;
};
}
