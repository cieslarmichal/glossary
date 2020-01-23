#pragma once

#include <memory>

#include "DescriptionsMemoryStorage.h"
#include "DescriptionsSerializer.h"
#include "DescriptionsStorage.h"
#include "FileAccess.h"

namespace wordsDb::descriptionsDb
{

class DescriptionsPersistentStorage : public DescriptionsStorage
{
public:
    DescriptionsPersistentStorage(
        std::shared_ptr<const FileAccess>,
        std::shared_ptr<const DescriptionsSerializer>);

    void addWordDescription(const WordDescription&) override;
    boost::optional<WordDescription>
    getWordDescription(const EnglishWord&) const override;
    WordsDescriptions getWordsDescriptions() const override;
    bool contains(const EnglishWord&) const override;
    WordsDescriptions::size_type size() const override;
    bool empty() const override;
    WordsDescriptions::const_iterator begin() const override;
    WordsDescriptions::const_iterator end() const override;

private:
    void loadFile();
    void serialize() const;

    std::shared_ptr<const FileAccess> fileAccess;
    std::shared_ptr<const DescriptionsSerializer> serializer;
    DescriptionsMemoryStorage storage;

    static const std::string directory;
    static const std::string filename;
};
}
