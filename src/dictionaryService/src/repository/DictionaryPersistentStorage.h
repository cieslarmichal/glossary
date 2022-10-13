#pragma once

#include <memory>

#include "../../../common/fileSystem/include/FileAccess.h"
#include "DictionaryMemoryStorage.h"
#include "DictionaryStorage.h"
#include "serialization/DictionarySerializer.h"

namespace glossary::dictionaryService::repository
{
class DictionaryPersistentStorage : public DictionaryStorage
{
public:
    DictionaryPersistentStorage(std::shared_ptr<const common::FileAccess>,
                                std::shared_ptr<const serialization::DictionarySerializer>);

    void addDictionary(const DictionaryName&) override;
    void addDictionary(const Dictionary&) override;
    void addWordToDictionary(const DictionaryWord&, const DictionaryName&) override;
    void removeDictionary(const DictionaryName&) override;
    void removeWordFromDictionary(const std::string&, const DictionaryName&) override;
    void changeWordTranslationFromDictionary(const std::string&, const std::string&,
                                             const DictionaryName&) override;
    boost::optional<Dictionary> getDictionary(const DictionaryName&) const override;
    Dictionaries getDictionaries() const override;
    bool containsDictionary(const DictionaryName&) const override;
    Dictionaries::size_type size() const override;
    bool empty() const override;

private:
    void loadFile();
    void serialize() const;

    std::shared_ptr<const common::FileAccess> fileAccess;
    std::shared_ptr<const serialization::DictionarySerializer> serializer;
    DictionaryMemoryStorage storage;

    static const std::string directory;
    static const std::string filename;
};
}
