#pragma once

#include <memory>

#include "DescriptionsStorage.h"
#include "FileAccess.h"
#include "wordsDb/descriptionsDb/DescriptionsSerializer.h"
#include "wordsDb/descriptionsDb/DescriptionsMemoryStorage.h"

namespace wordsDb::descriptionsDb
{

class DescriptionsPersistentStorage : public DescriptionsStorage
{
public:
    DescriptionsPersistentStorage(std::shared_ptr<const FileAccess>,
                      std::shared_ptr<const DescriptionsSerializer>);

    void addWord(const WordDescription&) override;
    boost::optional<WordDescription> getWord(const EnglishWord&) const override;
    Words getWords() const override;
    bool contains(const EnglishWord&) const override;
    Words::size_type size() const override;
    bool empty() const override;
    Words::const_iterator begin() const override;
    Words::const_iterator end() const override;

private:
    void loadFile();
    void serialize() const;

    std::shared_ptr<const FileAccess> fileAccess;
    std::shared_ptr<const DescriptionsSerializer> serializer;
    DescriptionsMemoryStorage storage;

    static const std::string fileDirectory;
    static const std::string fileName;
    static const std::string filePath;
};
}
