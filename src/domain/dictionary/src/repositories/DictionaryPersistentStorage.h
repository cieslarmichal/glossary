#pragma once

#include <memory>

#include "../serializers/DictionarySerializer.h"
#include "DictionaryMemoryStorage.h"
#include "DictionaryStorage.h"
#include "fileSystem/FileAccess.h"

namespace glossary::dictionary
{
class DictionaryPersistentStorage : public DictionaryStorage
{
public:
    DictionaryPersistentStorage(std::shared_ptr<const common::fileSystem::FileAccess>,
                                std::shared_ptr<const DictionarySerializer>);

    void addDictionary(const std::string&) override;
    void addDictionary(const Dictionary&) override;
    void addWordToDictionary(const DictionaryWord&, const std::string&) override;
    void removeDictionary(const std::string&) override;
    void removeWordFromDictionary(const std::string&, const std::string&) override;
    void changeWordTranslationFromDictionary(const std::string&, const std::string&, const std::string&) override;
    std::optional<Dictionary> getDictionary(const std::string&) const override;
    std::vector<Dictionary> getDictionaries() const override;
    bool containsDictionary(const std::string&) const override;
    std::vector<Dictionary>::size_type size() const override;
    bool empty() const override;

private:
    void loadFile();
    void serialize() const;

    std::shared_ptr<const common::fileSystem::FileAccess> fileAccess;
    std::shared_ptr<const DictionarySerializer> serializer;
    DictionaryMemoryStorage storage;

    static const std::string directory;
    static const std::string filename;
};
}
